#ifndef __DIFFUSION_H
#define __DIFFUSION_H

struct Point {
    double diffusivity;
    double x, y;
    double temperature;
    double residual;
    double source;
};

void read_png_file(char *filename, int *n_x_ptr, int *n_y_ptr);
void compute_mesh(struct Point points[], int n_x, int n_y,
                  double delta_x, double delta_y);
void set_diffusivities(struct Point points[], int n_x, int n_y,
                       double diffus_1, double diffus_2, double diffus_3);
void init_temperatures(struct Point points[], int points_length, double temp);
double calculate_sum(struct Point points[], int points_length);
double compute_step(struct Point points[], int n_x, int n_y, double timestep,
                    double delta_x, double delta_y);
int solve_diffusion(int print, struct Point points[], int n_x, int n_y,
                    double total_time, double initial_temp,
                    int i_bc, int j_bc, double source_val,
                    double diff_1, double diff_2, double diff_3);
void write_vtk(struct Point points[], int n_x, int n_y, int iter_number);
void write_res_vtk(struct Point points[], int n_x, int n_y, int iter_number);

#endif
