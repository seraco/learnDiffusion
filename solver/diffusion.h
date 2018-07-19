#ifndef __DIFFUSION_H
#define __DIFFUSION_H

struct Point {
    double diffusivity;
    double x, y;
    double temperature;
    double residual;
    double source;
};

void compute_mesh(struct Point points[], int n_x, int n_y,
                  double width, double height, double delta_x, double delta_y);
void set_diffusivities(struct Point points[], int n_x, int n_y,
                       double diffus_1, double diffus_2,
                       int i_1, int i_2, int j_1, int j_2);
void init_temperatures(struct Point points[], int points_length, double temp);
double compute_step(struct Point points[], int n_x, int n_y,
                    double width, double height, double timestep,
                    double delta_x, double delta_y);
int solve_diffusion(int print, struct Point points[], int n_x, int n_y,
                    double total_time, double initial_temp,
                    int i_bc, int j_bc, double source_val,
                    double diff_1, double diff_2,
                    int i_1, int i_2, int j_1, int j_2);
void write_vtk(struct Point points[], int n_x, int n_y, int iter_number);
void write_res_vtk(struct Point points[], int n_x, int n_y, int iter_number);

#endif
