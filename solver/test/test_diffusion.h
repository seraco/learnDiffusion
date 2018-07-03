#ifndef __TEST_DIFFUSION_H
#define __TEST_DIFFUSION_H

// #define KYEL "\x1B[33m"
#define KGRN "\x1B[32m"
#define KRED "\x1B[31m"
#define KNRM "\x1B[0m"

int test_cds_2();
int test_fds_1();
int test_bds_1();
int test_compute_mesh();
int test_set_diffusivities();
int test_init_temperatures();
int test_compute_step();
int test_solve_diffusion();
void run(char *file_name);
int success(char *file_name);
int failure(char *file_name);

#endif
