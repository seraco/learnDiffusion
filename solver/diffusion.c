#ifndef __DIFFUSION_C
#define __DIFFUSION_C

#include <stdio.h>
#include <math.h>

#include "diffusion.h"

void compute_mesh(struct Point points[], int n_x, int n_y,
                  double width, double height, double delta_x, double delta_y)
{
    int global;
    for (int j = 0; j < n_x; j++) {
        for (int i = 0; i < n_y; i++) {
            global = i + j * n_x;
            points[global].x = i * delta_x;
            points[global].y = j * delta_y;
        }
    }
}

void set_diffusivities(struct Point points[], int n_x, int n_y,
                       double diffus_1, double diffus_2,
                       int i_1, int i_2, int j_1, int j_2)
{
    int center;

    for (int j = 0; j < n_x; j++) {
        for (int i = 0; i < n_y; i++) {
            center = i + j * n_x;

            if (i < i_1 || i > i_2 || j < j_1 || j > j_2)
                points[center].diffusivity = diffus_1;
            else
                points[center].diffusivity = diffus_2;
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

double compute_step(struct Point points[], int n_x, int n_y,
                    double width, double height, double timestep,
                    double delta_x, double delta_y)
{
    int center, east, west, north, south;
    double x_y_term;
    double x_term, y_term;
    double max_res = 0.0;
    double rhs[n_x * n_y];

    for (int j = 1; j < n_x - 1; j++) {
        for (int i = 1; i < n_y - 1; i++) {
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

    for (int j = 1; j < n_x - 1; j++) {
        for (int i = 1; i < n_y - 1; i++) {
            center = i + j * n_x;

            points[center].temperature += rhs[center];
            points[center].residual = fabs(rhs[center]);
        }
    }

    return max_res;
}

int solve_diffusion(int print, struct Point points[], int n_x, int n_y,
                    double total_time, double initial_temp,
                    int i_bc, int j_bc, double source_val,
                    double diff_1, double diff_2,
                    int i_1, int i_2, int j_1, int j_2)
{
    double res = 10.0;
    int iter = 0, length = n_x * n_y;
    double d_x, d_y;
    double delta_space, timestep, side_size, max_diff;

    max_diff = diff_1 > diff_2 ? diff_1 : diff_2;
    side_size = sqrt(2 * max_diff * total_time);
    side_size /= 2;

    if (print)
        printf("Side size = %.10e\n", side_size);

    d_x = side_size / (n_x - 1);
    d_y = side_size / (n_y - 1);

    delta_space = d_x < d_y ? d_x : d_y;
    timestep = 0.25 * delta_space * delta_space / max_diff;
    timestep *= 0.98;

    if (print)
        printf("Delta time = %.10e\n", timestep);

    compute_mesh(points, n_x, n_y, side_size, side_size, d_x, d_y);
    set_diffusivities(points, n_x, n_y, diff_1, diff_2, i_1, i_2, j_1, j_2);
    init_temperatures(points, length, initial_temp);

    points[i_bc + j_bc * n_x].source = source_val;

    while (iter < (total_time / timestep)) {
        iter++;
        res = compute_step(points, n_x, n_y, side_size, side_size,
                           timestep, d_x, d_y);

        if (print && (iter % 1000 == 0))
                printf("Residual = %.10e, Number of iterations = %d\n",
                        res, iter);

        // if (iter % 10000 == 0) {
        //     write_vtk(points, n_x, n_y, iter / 10000);
        //     write_res_vtk(points, n_x, n_y, iter / 10000);
        // }
    }

    if (print)
        printf("Residual = %.10e, Number of iterations = %d\n", res, iter);

    write_vtk(points, n_x, n_y, 0);
    write_res_vtk(points, n_x, n_y, 0);

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
