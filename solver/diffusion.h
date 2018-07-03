#ifndef __DIFFUSION_H
#define __DIFFUSION_H

struct Point {
    double diffusivity;
    double x, y;
    int x_index, y_index;
    int global_index;
    double temperature;
};

double cds_2(double right, double left, double separation);
double fds_1(double right, double center, double separation);
double bds_1(double center, double left, double separation);
void compute_mesh(struct Point points[], int n_x, int n_y,
                  double width, double height);
void set_diffusivities(struct Point points[], int points_length, double diffus);
void init_temperatures(struct Point points[], int points_length, double temp);
double compute_step(struct Point points[], int n_x, int n_y,
                    double width, double height, double timestep);
int solve_diffusion(int print, struct Point points[], int n_x, int n_y,
                    double width, double height, double timestep,
                    double initial_temp);

#endif
