#ifndef __DIFFUSION_H
#define __DIFFUSION_H

struct Point {
    double diffusivity;
    double x, y;
    int x_index, y_index;
    int global_index;
    double value;
};

double cds_2(double right, double left, double separation);
void compute_mesh(struct Point points[], int n_x, int n_y,
                  double width, double height);

#endif
