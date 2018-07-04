#ifndef __DIFFUSION_C
#define __DIFFUSION_C

#include <stdio.h>
#include <math.h>

#include "diffusion.h"

double cds_2(double right, double left, double separation)
{
    return (right - left) / 2 / separation;
}

double fds_1(double right, double center, double separation)
{
    return (right - center) / separation;
}

double bds_1(double center, double left, double separation)
{
    return (center - left) / separation;
}

void compute_mesh(struct Point points[], int n_x, int n_y,
                  double width, double height)
{
    int global;
    double d_x = width / (n_x - 1);
    double d_y = height / (n_y - 1);
    for (int j = 0; j < n_x; j++) {
        for (int i = 0; i < n_y; i++) {
            global = i + j * n_x;
            points[global].global_index = global;
            points[global].x_index = i;
            points[global].y_index = j;
            points[global].x = i * d_x;
            points[global].y = j * d_y;
        }
    }
}

void set_diffusivities(struct Point points[], int points_length,
                       double diffus_1, double diffus_2,
                       double x_1, double x_2, double y_1, double y_2)
{
    for (int k = 0; k < points_length; k++) {
        if (points[k].x < x_1 || points[k].x > x_2)
            points[k].diffusivity = diffus_1;
        else
            points[k].diffusivity = diffus_2;
    }
}

void init_temperatures(struct Point points[], int points_length, double temp)
{
    for (int k = 0; k < points_length; k++) {
        points[k].temperature = temp;
    }
}

double compute_step(struct Point points[], int n_x, int n_y,
                    double width, double height, double timestep,
                    double x_bc, double y_bc, double temp_bc)
{
    int center, east, west, north, south;
    double d_x = width / (n_x - 1);
    double d_y = height / (n_y - 1);
    double rhs[n_x * n_y];
    double x_term_east, x_term_west, x_term;
    double y_term_south, y_term_north, y_term;
    double max_res = 0.0;

    for (int j = 1; j < n_x - 1; j++) {
        for (int i = 1; i < n_y - 1; i++) {
            center = i + j * n_x;
            if (fabs(points[center].x - x_bc) < 1.1 * d_x
                && fabs(points[center].y - y_bc) < 1.1 * d_y)
                points[center].temperature = temp_bc;
        }
    }

    for (int j = 1; j < n_x - 1; j++) {
        for (int i = 1; i < n_y - 1; i++) {
            center = i + j * n_x;
            east = (i + 1) + j * n_x;
            west = (i - 1) + j * n_x;
            north = i + (j + 1) * n_x;
            south = i + (j - 1) * n_x;

            x_term_east = bds_1(points[east].temperature,
                                points[center].temperature,
                                d_x);
            x_term_west = fds_1(points[center].temperature,
                                points[west].temperature,
                                d_x);

            y_term_north = bds_1(points[north].temperature,
                                 points[center].temperature,
                                 d_y);
            y_term_south = fds_1(points[center].temperature,
                                 points[south].temperature,
                                 d_y);

            x_term = cds_2(x_term_east * points[east].diffusivity,
                           x_term_west * points[west].diffusivity,
                           d_x);
            y_term = cds_2(y_term_north * points[north].diffusivity,
                           y_term_south * points[south].diffusivity,
                           d_y);

            rhs[center] = x_term + y_term;
            if (fabs(rhs[center]) > max_res)
                max_res = rhs[center];
        }
    }

    for (int j = 1; j < n_x - 1; j++) {
        for (int i = 1; i < n_y - 1; i++) {
            center = i + j * n_x;
            points[center].temperature = points[center].temperature
                                         + timestep * rhs[center];
        }
    }

    return max_res;
}

int solve_diffusion(int print, struct Point points[], int n_x, int n_y,
                    double width, double height, double timestep,
                    double initial_temp,
                    double x_bc, double y_bc, double temp_bc)
{
    double res = 10.0;
    int iter = 0, length = n_x * n_y;

    compute_mesh(points, n_x, n_y, width, height);
    set_diffusivities(points, length, 1e-5, 2e-5, 0.25, 0.75, 0.25, 0.75);
    init_temperatures(points, length, initial_temp);

    while (res > 0.0001) {
        iter++;
        res = compute_step(points, n_x, n_y, width, height, timestep,
                           x_bc, y_bc, temp_bc);
        if (print && (iter % 1000 == 0))
            printf("Residual = %f\n", res);
    }
    if (print)
        printf("Residual = %f\n", res);

    write_vtk(points, n_x, n_y);

    return iter;
}

void write_vtk(struct Point points[], int n_x, int n_y)
{
    FILE *f_ptr;
    int length = n_x * n_y;

    f_ptr = fopen("solution.vtk", "w");
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

#endif
