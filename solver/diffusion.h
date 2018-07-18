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
void set_diffusivities(struct Point points[], int points_length,
                       double diffus_1, double diffus_2,
                       double x_1, double x_2, double y_1, double y_2);
void init_temperatures(struct Point points[], int points_length, double temp);
double compute_step(struct Point points[], int n_x, int n_y,
                    double width, double height, double timestep,
                    int indexes_bc[], int length_idx_bc, double temp_bc,
                    double delta_x, double delta_y);
int solve_diffusion(int print, struct Point points[], int n_x, int n_y,
                    double width, double height, double timestep,
                    double initial_temp,
                    double x_bc, double y_bc, double temp_bc,
                    double diff_1, double diff_2,
                    double x_1, double x_2, double y_1, double y_2);
void write_vtk(struct Point points[], int n_x, int n_y, int iter_number);
void write_res_vtk(struct Point points[], int n_x, int n_y, int iter_number);

#endif
