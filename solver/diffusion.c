#ifndef __DIFFUSION_C
#define __DIFFUSION_C

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <png.h>

#include "diffusion.h"

int width, height;
png_byte color_type;
png_byte bit_depth;
png_bytep *row_pointers;

void read_png_file(char *filename, int *n_x_ptr, int *n_y_ptr)
{
    FILE *fp = fopen(filename, "rb");

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) abort();

    png_infop info = png_create_info_struct(png);
    if (!info) abort();

    if (setjmp(png_jmpbuf(png))) abort();

    png_init_io(png, fp);

    png_read_info(png, info);

    width      = png_get_image_width(png, info);
    height     = png_get_image_height(png, info);
    color_type = png_get_color_type(png, info);
    bit_depth  = png_get_bit_depth(png, info);

    if (bit_depth == 16)
        png_set_strip_16(png);

    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);

    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);

    if (png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);

    if (color_type == PNG_COLOR_TYPE_RGB ||
       color_type == PNG_COLOR_TYPE_GRAY ||
       color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

    if (color_type == PNG_COLOR_TYPE_GRAY ||
       color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
       png_set_gray_to_rgb(png);

    png_read_update_info(png, info);

    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++) {
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
    }

    png_read_image(png, row_pointers);

    *n_x_ptr = width;
    *n_y_ptr = height;

    fclose(fp);
}

void compute_mesh(struct Point points[], int n_x, int n_y,
                  double delta_x, double delta_y)
{
    int center;
    for (int j = 0; j < n_y; j++) {
        for (int i = 0; i < n_x; i++) {
            center = i + j * n_x;
            points[center].x = i * delta_x;
            points[center].y = j * delta_y;
        }
    }
}

void set_diffusivities(struct Point points[], int n_x, int n_y,
                       double diffus_1, double diffus_2, double diffus_3)
{
    int center;
    for (int y = 0; y < height; y++) {
        png_bytep row = row_pointers[y];
        for (int x = 0; x < width; x++) {
            center = x + y * width;
            png_bytep px = &(row[x * 4]);
            if (px[0] == 255)
                points[center].diffusivity = diffus_1;
            else if (px[0] == 0)
                points[center].diffusivity = diffus_2;
            else
                points[center].diffusivity = diffus_3;
        }
    }
}

void init_values(struct Point points[], int points_length, double val)
{
    for (int k = 0; k < points_length; k++) {
        points[k].value = val;
        points[k].residual = 0.0;
        points[k].source = 0.0;
    }
}

void internal_conditions(struct Point points[], int points_length,
                         double x_bc, double y_bc, double source_val,
                         double size)
{
    double p_size = size / 100.0;
    for (int k = 0; k < points_length; k++) {
        if ((points[k].x > x_bc - p_size) && (points[k].x < x_bc + p_size)
            && (points[k].y > y_bc - p_size) && (points[k].y < y_bc + p_size)) {
            points[k].value = source_val;
        }
    }
}

double apparent_diffusion(struct Point points[], int points_length,
                          double x_bc, double y_bc, double total_time)
{
    double d_r, sum = 0.0;
    for (int k = 0; k < points_length; k++) {
        double x_s = points[k].x - x_bc;
        x_s *= x_s;
        double y_s = points[k].y - y_bc;
        y_s *= y_s;
        d_r = sqrt(x_s + y_s);
        double conc = points[k].value * d_r;
        conc *= conc;
        sum += conc;
    }

    return sqrt(sum) / total_time / 4;
}

double calculate_sum(struct Point points[], int points_length)
{
    double sum = 0.0;
    for (int k = 0; k < points_length; k++) {
        sum += points[k].value;
    }

    return sum;
}

double explicit_rhs(struct Point points[], int center, int east, int west,
                    int north, int south, double timestep,
                    double delta_x, double delta_y)
{
    double res;
    double coef_east = points[east].diffusivity * timestep / delta_x / delta_x;
    double coef_west = points[west].diffusivity * timestep / delta_x / delta_x;
    double coef_north = points[north].diffusivity * timestep / delta_y / delta_y;
    double coef_south = points[south].diffusivity * timestep / delta_y / delta_y;

    res = (- coef_east - coef_west) * points[center].value;
    res += coef_east * points[east].value;
    res += coef_west * points[west].value;
    res += (- coef_north - coef_south) * points[center].value;
    res += coef_north * points[north].value;
    res += coef_south * points[south].value;
    res += timestep * points[center].source;

    return res;
}

double implicit_rhs(struct Point points[], int center, int east, int west,
                    int north, int south, double timestep,
                    double delta_x, double delta_y)
{
    double res;
    double coef_east = points[east].diffusivity * timestep / delta_x / delta_x;
    double coef_west = points[west].diffusivity * timestep / delta_x / delta_x;
    double coef_north = points[north].diffusivity * timestep / delta_y / delta_y;
    double coef_south = points[south].diffusivity * timestep / delta_y / delta_y;
    double coef_impl = 1 + coef_east + coef_west + coef_north + coef_south;

    res = coef_east * points[east].value + coef_west * points[west].value;
    res += coef_north * points[north].value + coef_south * points[south].value;
    res /= coef_impl;
    res += (1 / coef_impl - 1) * points[center].value;
    res += timestep * points[center].source;

    return res;
}

double compute_step(struct Point points[], int n_x, int n_y, double timestep,
                    double delta_x, double delta_y, int shifter, int hopscotch)
{
    int center, east, west, north, south;
    double rhs_term;
    double max_res = 0.0;
    double rhs[n_x * n_y];

    for (int j = 1; j < n_y - 1; j++) {
        for (int i = 1; i < n_x - 1; i++) {
            center = i + j * n_x;
            int even_even = i % 2 == 0 && j % 2 == 0;
            int odd_odd = i % 2 == 1 && j % 2 == 1;
            int should_continue = even_even || odd_odd;
            if (hopscotch && should_continue == shifter)
                continue;
            east = (i + 1) + j * n_x, west = (i - 1) + j * n_x;
            north = i + (j + 1) * n_x, south = i + (j - 1) * n_x;

            rhs_term = explicit_rhs(points, center, east, west, north, south,
                                    timestep, delta_x, delta_y);

            if (fabs(rhs_term) > max_res)
                max_res = fabs(rhs_term);

            rhs[center] = rhs_term;
        }
    }

    for (int j = 1; j < n_y - 1; j++) {
        for (int i = 1; i < n_x - 1; i++) {
            center = i + j * n_x;
            int even_even = i % 2 == 0 && j % 2 == 0;
            int odd_odd = i % 2 == 1 && j % 2 == 1;
            int should_continue = even_even || odd_odd;
            if (hopscotch && should_continue == shifter)
                continue;
            // printf("%d ", center);
            points[center].value += rhs[center];
            points[center].residual = fabs(rhs[center]);
        }
    }

    // printf("===============================================================\n");

    if (hopscotch) {
        for (int j = 1; j < n_y - 1; j++) {
            for (int i = 1; i < n_x - 1; i++) {
                center = i + j * n_x;
                int even_even = i % 2 == 0 && j % 2 == 0;
                int odd_odd = i % 2 == 1 && j % 2 == 1;
                int should_continue = even_even || odd_odd;
                if (should_continue != shifter)
                    continue;
                east = (i + 1) + j * n_x, west = (i - 1) + j * n_x;
                north = i + (j + 1) * n_x, south = i + (j - 1) * n_x;

                rhs_term = implicit_rhs(points, center, east, west, north, south,
                                        timestep, delta_x, delta_y);

                if (fabs(rhs_term) > max_res)
                    max_res = fabs(rhs_term);

                rhs[center] = rhs_term;
            }
        }

        for (int j = 1; j < n_y - 1; j++) {
            for (int i = 1; i < n_x - 1; i++) {
                center = i + j * n_x;
                int even_even = i % 2 == 0 && j % 2 == 0;
                int odd_odd = i % 2 == 1 && j % 2 == 1;
                int should_continue = even_even || odd_odd;
                if (should_continue != shifter)
                    continue;
                // printf("%d ", center);
                points[center].value += rhs[center];
                points[center].residual = fabs(rhs[center]);
            }
        }
        // printf("***************************************************************\n");
    }

    for (int i = 1; i < n_x - 1; i++) {
        center = i + 0 * n_x;
        north = i + (0 + 1) * n_x;

        points[center].value = points[north].value;
    }

    for (int i = 1; i < n_x - 1; i++) {
        center = i + (n_y - 1) * n_x;
        south = i + ((n_y - 1) - 1) * n_x;

        points[center].value = points[south].value;
    }

    for (int j = 1; j < n_y - 1; j++) {
        center = 0 + j * n_x;
        east = (0 + 1) + j * n_x;

        points[center].value = points[east].value;
    }

    for (int j = 1; j < n_y - 1; j++) {
        center = (n_x - 1) + j * n_x;
        west = ((n_x - 1) - 1) + j * n_x;

        points[center].value = points[west].value;
    }

    center = 0 + 0 * n_x;
    east = 1 + 0 * n_x;
    points[center].value = points[east].value;
    center = (n_x - 1) + 0 * n_x;
    west = ((n_x - 1) - 1) + 0 * n_x;
    points[center].value = points[west].value;
    center = 0 + (n_y - 1) * n_x;
    east = 1 + (n_y - 1) * n_x;
    points[center].value = points[east].value;
    center = (n_x - 1) + (n_y - 1) * n_x;
    west = ((n_x - 1) - 1) + (n_y - 1) * n_x;
    points[center].value = points[west].value;

    return max_res;
}

void gaussian_analytical(struct Point points[], int length, double current_time,
                         double diff, double x_bc, double y_bc)
{
    for (int k = 0; k < length; k++) {
      double x_shifted = points[k].x - x_bc;
      double y_shifted = points[k].y - y_bc;
      double r_sqr = x_shifted * x_shifted + y_shifted * y_shifted;
      points[k].analytical_value = exp(-r_sqr / 4 / diff / current_time);
      points[k].analytical_value /= (4 * M_PI * current_time * diff);
    }
}

int solve_diffusion(int print, struct Point points[], int n_x, int n_y,
                    double total_time, double initial_val,
                    double x_perc_bc, double y_perc_bc, double source_val,
                    double diff_1, double diff_2, double diff_3)
{
    double res = 10.0, sum;
    int iter = 0, length = n_x * n_y;
    double d_x, d_y;
    double delta_space, timestep, max_diff;
    double x_side_size, y_side_size;
    double current_time = 0.0;

    max_diff = diff_1 > diff_2 ? diff_1 : diff_2;
    max_diff = diff_3 > max_diff ? diff_3 : max_diff;
    // x_side_size = sqrt(2 * max_diff * total_time);
    // y_side_size = x_side_size;
    x_side_size = 7.75e-05;
    y_side_size = x_side_size;
    d_x = x_side_size / (n_x - 1);
    d_y = y_side_size / (n_y - 1);
    delta_space = d_x < d_y ? d_x : d_y;
    timestep = 0.25 * delta_space * delta_space / max_diff;
    timestep *= 0.98;
    // printf("Delta time theory = %.10e\n", timestep);
    // timestep = 1e-8;

    if (print) {
        printf("X number nodes = %d, Y number nodes = %d\n",
                n_x, n_y);
        printf("X side size = %.10e, Y side size = %.10e\n",
                x_side_size, y_side_size);
        printf("Delta X = %.10e, Delta Y = %.10e\n",
                d_x, d_y);
        printf("Delta time = %.10e\n", timestep);
    }

    compute_mesh(points, n_x, n_y, d_x, d_y);
    set_diffusivities(points, n_x, n_y, diff_1, diff_2, diff_3);
    init_values(points, length, initial_val);

    double x_bc = x_side_size * x_perc_bc;
    double y_bc = y_side_size * y_perc_bc;
    double max_size = x_side_size > y_side_size ? x_side_size : y_side_size;

    internal_conditions(points, length, x_bc, y_bc, source_val, max_size);

    int f_name = 0;
    write_vtk(points, n_x, n_y, f_name);
    // gaussian_analytical(points, length, current_time, max_diff, x_bc, y_bc);
    // write_vtk_anal(points, n_x, n_y, f_name);
    f_name++;

    double plot_every = 1e-4;
    double factor_to_compare = 1.0 / plot_every;

    int shifter = 0, hops = 0;
    double app_diff;

    while (iter < (total_time / timestep)) {
        iter++;
        current_time += timestep;
        shifter = !shifter;
        res = compute_step(points, n_x, n_y, timestep, d_x, d_y, shifter, hops);
        sum = calculate_sum(points, length);
        app_diff = apparent_diffusion(points, length, x_bc, y_bc, total_time);

        double tmp_time = current_time / plot_every;
        double difference = tmp_time - floor(tmp_time);

        if (print && difference < timestep * factor_to_compare) {
                printf("Res = %.4e, Sum = %.4e, Iter = %d, ", res, sum, iter);
                printf("Time = %.4e, ADC = %.4e, Fname = %d\n",
                       current_time, app_diff, f_name);
        }

        if (difference < timestep * factor_to_compare) {
            write_vtk(points, n_x, n_y, f_name);
            // write_res_vtk(points, n_x, n_y, f_name);
            // gaussian_analytical(points, length, current_time, max_diff, x_bc, y_bc);
            // write_vtk_anal(points, n_x, n_y, f_name);
            f_name++;
        }
    }

    return iter;
}

void write_vtk(struct Point points[], int n_x, int n_y, int iter_number)
{
    FILE *f_ptr;
    int length = n_x * n_y;
    char buffer[256];

    sprintf(buffer, "../sol/solution%d.vtk", iter_number);

    f_ptr = fopen(buffer, "w");
    fprintf(f_ptr, "# vtk DataFile Version 2.0\n");
    fprintf(f_ptr, "Diffusion solution\n");
    fprintf(f_ptr, "ASCII\n");
    fprintf(f_ptr, "DATASET STRUCTURED_GRID\n");
    fprintf(f_ptr, "DIMENSIONS %d %d 1\n", n_x, n_y);
    fprintf(f_ptr, "POINTS %d double\n", length);

    for (int k = 0; k < length; k++) {
        double x, y;
        x = points[k].x;
        y = points[k].y;
        fprintf(f_ptr, "%.10e %.10e 0.0\n", x, y);
    }

    fprintf(f_ptr, "POINT_DATA %d\n", length);
    fprintf(f_ptr, "FIELD FieldData 1\n");
    fprintf(f_ptr, "Val 1 %d double\n", length);

    for (int k = 0; k < length; k++) {
        double val;
        val = points[k].value;
        fprintf(f_ptr, "%.10e\n", val);
    }

    fclose(f_ptr);
}

void write_vtk_anal(struct Point points[], int n_x, int n_y, int iter_number)
{
    FILE *f_ptr;
    int length = n_x * n_y;
    char buffer[256];

    sprintf(buffer, "../sol/analytical%d.vtk", iter_number);

    f_ptr = fopen(buffer, "w");
    fprintf(f_ptr, "# vtk DataFile Version 2.0\n");
    fprintf(f_ptr, "Diffusion solution\n");
    fprintf(f_ptr, "ASCII\n");
    fprintf(f_ptr, "DATASET STRUCTURED_GRID\n");
    fprintf(f_ptr, "DIMENSIONS %d %d 1\n", n_x, n_y);
    fprintf(f_ptr, "POINTS %d double\n", length);

    for (int k = 0; k < length; k++) {
        double x, y;
        x = points[k].x;
        y = points[k].y;
        fprintf(f_ptr, "%.10e %.10e 0.0\n", x, y);
    }

    fprintf(f_ptr, "POINT_DATA %d\n", length);
    fprintf(f_ptr, "FIELD FieldData 1\n");
    fprintf(f_ptr, "Anal 1 %d double\n", length);

    for (int k = 0; k < length; k++) {
        double val;
        val = points[k].analytical_value;
        fprintf(f_ptr, "%.10e\n", val);
    }

    fclose(f_ptr);
}

void write_res_vtk(struct Point points[], int n_x, int n_y, int iter_number)
{
    FILE *f_ptr;
    int length = n_x * n_y;
    char buffer[256];

    sprintf(buffer, "../sol/residual%d.vtk", iter_number);

    f_ptr = fopen(buffer, "w");
    fprintf(f_ptr, "# vtk DataFile Version 2.0\n");
    fprintf(f_ptr, "Diffusion solution\n");
    fprintf(f_ptr, "ASCII\n");
    fprintf(f_ptr, "DATASET STRUCTURED_GRID\n");
    fprintf(f_ptr, "DIMENSIONS %d %d 1\n", n_x, n_y);
    fprintf(f_ptr, "POINTS %d double\n", length);

    for (int k = 0; k < length; k++) {
        double x, y;
        x = points[k].x;
        y = points[k].y;
        fprintf(f_ptr, "%.10e %.10e 0.0\n", x, y);
    }

    fprintf(f_ptr, "POINT_DATA %d\n", length);
    fprintf(f_ptr, "FIELD FieldData 1\n");
    fprintf(f_ptr, "Residual 1 %d double\n", length);

    for (int k = 0; k < length; k++) {
        double res;
        res = points[k].residual;
        fprintf(f_ptr, "%.10e\n", res);
    }

    fclose(f_ptr);
}

#endif
