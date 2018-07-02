#ifndef __DIFFUSION_C
#define __DIFFUSION_C

#include "diffusion.h"

double cds_2(double right, double left, double separation)
{
    return (right - left) / 2 / separation;
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

#endif
