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

void read_png_file(char *filename, int *n_x_ptr, int *n_y_ptr) {
    FILE *fp = fopen(filename, "rb");

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png) abort();

    png_infop info = png_create_info_struct(png);
    if(!info) abort();

    if(setjmp(png_jmpbuf(png))) abort();

    png_init_io(png, fp);

    png_read_info(png, info);

    width      = png_get_image_width(png, info);
    height     = png_get_image_height(png, info);
    color_type = png_get_color_type(png, info);
    bit_depth  = png_get_bit_depth(png, info);

    if(bit_depth == 16)
        png_set_strip_16(png);

    if(color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png);

    if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png);

    if(png_get_valid(png, info, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png);

    if(color_type == PNG_COLOR_TYPE_RGB ||
       color_type == PNG_COLOR_TYPE_GRAY ||
       color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

    if(color_type == PNG_COLOR_TYPE_GRAY ||
       color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
       png_set_gray_to_rgb(png);

    png_read_update_info(png, info);

    row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for(int y = 0; y < height; y++) {
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

    for(int y = 0; y < height; y++) {
        png_bytep row = row_pointers[y];
        for(int x = 0; x < width; x++) {
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

void init_temperatures(struct Point points[], int points_length, double temp)
{
    for (int k = 0; k < points_length; k++) {
        points[k].temperature = temp;
        points[k].residual = 0.0;
        points[k].source = 0.0;
    }
}

double calculate_sum(struct Point points[], int points_length)
{
    double sum = 0.0;

    for (int k = 0; k < points_length; k++) {
        sum += points[k].temperature;
    }

    return sum;
}

double compute_step(struct Point points[], int n_x, int n_y, double timestep,
                    double delta_x, double delta_y)
{
    int center, east, west, north, south;
    double x_y_term;
    double x_term, y_term;
    double max_res = 0.0;
    double rhs[n_x * n_y];

    for (int j = 1; j < n_y - 1; j++) {
        for (int i = 1; i < n_x - 1; i++) {
            center = i + j * n_x;
            east = (i + 1) + j * n_x;
            west = (i - 1) + j * n_x;
            north = i + (j + 1) * n_x;
            south = i + (j - 1) * n_x;

            x_term = points[east].diffusivity * (points[east].temperature
                     - points[center].temperature);
            x_term -= points[west].diffusivity * (points[center].temperature
                      - points[west].temperature);
            x_term = x_term / delta_x / delta_x;

            y_term = points[north].diffusivity * (points[north].temperature
                     - points[center].temperature);
            y_term -= points[south].diffusivity * (points[center].temperature
                      - points[south].temperature);
            y_term = y_term / delta_y / delta_y;

            x_y_term = timestep * (x_term + y_term + points[center].source);

            if (fabs(x_y_term) > max_res)
                max_res = fabs(x_y_term);


            // points[center].temperature += x_y_term;
            rhs[center] = x_y_term;
        }
    }

    for (int j = 1; j < n_y - 1; j++) {
        for (int i = 1; i < n_x - 1; i++) {
            center = i + j * n_x;

            points[center].temperature += rhs[center];
            points[center].residual = fabs(rhs[center]);
        }
    }

    for (int i = 1; i < n_x - 1; i++) {
        center = i + 0 * n_x;
        north = i + (0 + 1) * n_x;
        // printf("Center: %d (x: %f, y: %f), North: %d (x: %f, y: %f)\n",
        //         center, points[center].x, points[center].y,
        //         north, points[north].x, points[north].y);

        points[center].temperature = points[north].temperature;
    }

    for (int i = 1; i < n_x - 1; i++) {
        center = i + (n_y - 1) * n_x;
        south = i + ((n_y - 1) - 1) * n_x;
        // printf("Center: %d (x: %f, y: %f), South: %d (x: %f, y: %f)\n",
        //         center, points[center].x, points[center].y,
        //         south, points[south].x, points[south].y);

        points[center].temperature = points[south].temperature;
    }

    for (int j = 1; j < n_y - 1; j++) {
        center = 0 + j * n_x;
        east = (0 + 1) + j * n_x;

        points[center].temperature = points[east].temperature;
    }

    for (int j = 1; j < n_y - 1; j++) {
        center = (n_x - 1) + j * n_x;
        west = ((n_x - 1) - 1) + j * n_x;

        points[center].temperature = points[west].temperature;
    }

    center = 0 + 0 * n_x;
    east = 1 + 0 * n_x;
    points[center].temperature = points[east].temperature;
    center = (n_x - 1) + 0 * n_x;
    west = ((n_x - 1) - 1) + 0 * n_x;
    points[center].temperature = points[west].temperature;
    center = 0 + (n_y - 1) * n_x;
    east = 1 + (n_y - 1) * n_x;
    points[center].temperature = points[east].temperature;
    center = (n_x - 1) + (n_y - 1) * n_x;
    west = ((n_x - 1) - 1) + (n_y - 1) * n_x;
    points[center].temperature = points[west].temperature;

    return max_res;
}

int solve_diffusion(int print, struct Point points[], int n_x, int n_y,
                    double total_time, double initial_temp,
                    int i_bc, int j_bc, double source_val,
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
    x_side_size = sqrt(2 * max_diff * total_time);
    y_side_size = x_side_size;
    // x_side_size = 7.7e-3;
    // y_side_size = x_side_size;

    if (print)
        printf("X side size = %.10e, Y side size = %.10e\n",
                x_side_size, y_side_size);

    d_x = x_side_size / (n_x - 1);
    d_y = y_side_size / (n_y - 1);

    delta_space = d_x < d_y ? d_x : d_y;
    timestep = 0.25 * delta_space * delta_space / max_diff;
    timestep *= 0.98;

    if (print)
        printf("Delta time = %.10e\n", timestep);

    compute_mesh(points, n_x, n_y, d_x, d_y);
    set_diffusivities(points, n_x, n_y, diff_1, diff_2, diff_3);
    init_temperatures(points, length, initial_temp);

    i_bc = n_x / 4;
    j_bc = n_y / 2;
    // points[i_bc + j_bc * n_x].source = source_val;
    points[i_bc + j_bc * n_x].temperature = source_val;

    write_vtk(points, n_x, n_y, 0);

    while (iter < (total_time / timestep)) {
        iter++;
        current_time += timestep;
        res = compute_step(points, n_x, n_y, timestep, d_x, d_y);
        sum = calculate_sum(points, length);

        double tmp_time = current_time / 0.01;
        double difference = tmp_time - floor(tmp_time);
        double factor_to_compare = 100.0;

        if (print && difference < timestep * factor_to_compare)
                printf("Res = %.4e, Sum = %.4e, Iter = %d, Time = %.4e, Fname = %d\n",
                        res, sum, iter, current_time,
                        (int) (current_time * factor_to_compare));

        if (difference < timestep * factor_to_compare) {
            write_vtk(points, n_x, n_y, (int) (current_time * factor_to_compare));
            // write_res_vtk(points, n_x, n_y, (int) (current_time * factor_to_compare));
        }
    }

    // if (print)
    //     printf("Res = %.4e, Sum = %.4e, Iter = %d, Time = %.4e\n",
    //             res, sum, iter, current_time);

    // write_vtk(points, n_x, n_y, 0);
    // write_res_vtk(points, n_x, n_y, 0);

    return iter;
}

void write_vtk(struct Point points[], int n_x, int n_y, int iter_number)
{
    FILE *f_ptr;
    int length = n_x * n_y;
    char buffer[256];

    sprintf(buffer, "solution%d.vtk", iter_number);

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
        fprintf(f_ptr, "%f %f 0.0\n", x, y);
    }

    fprintf(f_ptr, "POINT_DATA %d\n", length);
    fprintf(f_ptr, "FIELD FieldData 1\n");
    fprintf(f_ptr, "Temperature 1 %d double\n", length);

    for (int k = 0; k < length; k++) {
        double temp;
        temp = points[k].temperature;
        fprintf(f_ptr, "%f\n", temp);
    }

    fclose(f_ptr);
}

void write_res_vtk(struct Point points[], int n_x, int n_y, int iter_number)
{
    FILE *f_ptr;
    int length = n_x * n_y;
    char buffer[256];

    sprintf(buffer, "residual%d.vtk", iter_number);

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
        fprintf(f_ptr, "%f %f 0.0\n", x, y);
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
