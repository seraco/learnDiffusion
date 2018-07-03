#ifndef __DIFFUSION_C
#define __DIFFUSION_C

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

void set_diffusivities(struct Point points[], int points_length, double diffus)
{
    for (int k = 0; k < points_length; k++) {
        points[k].diffusivity = diffus;
    }
}

void init_temperatures(struct Point points[], int points_length, double temp)
{
    for (int k = 0; k < points_length; k++) {
        points[k].temperature = temp;
    }
}

void compute_step(struct Point points[], int n_x, int n_y,
                  double width, double height, double timestep)
{
    int center, east, west, north, south;
    double d_x = width / (n_x - 1);
    double d_y = height / (n_y - 1);
    double rhs[n_x * n_y];
    double x_term_east, x_term_west, x_term;
    double y_term_south, y_term_north, y_term;
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
        }
    }

    for (int j = 1; j < n_x - 1; j++) {
        for (int i = 1; i < n_y - 1; i++) {
            center = i + j * n_x;
            points[center].temperature = points[center].temperature
                                         + timestep * rhs[center];
        }
    }
}

// void solve_diffusion(struct Point points[], int n_x, int n_y)
// {
//     int east, west, north, south;
//     double d_x = width / (n_x - 1);
//     double d_y = height / (n_y - 1);
//     double rhs[n_x * n_y];
//     double x_term, y_term;
//     for (int j = 1; j < n_x - 1; j++) {
//         for (int i = 1; i < n_y - 1; i++) {
//             center = i + j * n_x;
//             east = (i + 1) + j * n_x;
//             west = (i - 1) + j * n_x;
//             north = i + (j + 1) * n_x;
//             south = i + (j - 1) * n_x;
//
//             x_term_east = bds_1(points[east].temperature,
//                                 points[center].temperature,
//                                 d_x);
//             x_term_west = fds_1(points[center].temperature,
//                                 points[west].temperature,
//                                 d_x);
//
//             y_term_north = bds_1(points[north].temperature,
//                                  points[center].temperature,
//                                  d_y);
//             y_term_south = fds_1(points[center].temperature,
//                                  points[south].temperature,
//                                  d_y);
//
//             x_term = cds_2(x_term_east * points[east].diffusivity,
//                            x_term_west * points[west].diffusivity,
//                            d_x);
//             y_term = cds_2(y_term_north * points[north].diffusivity,
//                            y_term_south * points[south].diffusivity,
//                            d_y);
//
//             rhs[global] = x_term + y_term;
//         }
//     }
// }

#endif
