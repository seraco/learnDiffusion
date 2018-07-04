#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "diffusion.h"
#include "test_diffusion.h"

int main()
{
    if (test_cds_2()
        || test_fds_1()
        || test_bds_1()
        || test_compute_mesh()
        || test_set_diffusivities()
        || test_init_temperatures()
        || test_compute_step()
        || test_solve_diffusion())
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int test_cds_2()
{
    char *f_name = "cds_2";
    run(f_name);

    double a, b, delta_x;

    a = 1.0, b = 1.0, delta_x = 2.0;
    // printf("%f\n", cds_2(b, a, delta_x));
    if (fabs(cds_2(b, a, delta_x) - 0.0) >= 0.0001)
        return failure(f_name);

    a = 1.0, b = 3.0;
    // printf("%f\n", cds_2(b, a, delta_x));
    if (fabs(cds_2(b, a, delta_x) - 0.5) >= 0.0001)
        return failure(f_name);

    a = 3.0, b = 1.0;
    // printf("%f\n", cds_2(b, a, delta_x));
    if (fabs(cds_2(b, a, delta_x) + 0.5) >= 0.0001)
        return failure(f_name);

    // TODO: Study divide by zero error

    return success(f_name);
}

int test_fds_1()
{
    char *f_name = "fds_1";
    run(f_name);

    double a, b, delta_x;

    a = 1.0, b = 1.0, delta_x = 2.0;
    if (fabs(fds_1(b, a, delta_x) - 0.0) >= 0.0001)
        return failure(f_name);

    a = 1.0, b = 3.0;
    if (fabs(fds_1(b, a, delta_x) - 1.0) >= 0.0001)
        return failure(f_name);

    a = 3.0, b = 1.0;
    if (fabs(fds_1(b, a, delta_x) + 1.0) >= 0.0001)
        return failure(f_name);

    // TODO: Study divide by zero error

    return success(f_name);
}

int test_bds_1()
{
    char *f_name = "bds_1";
    run(f_name);

    double a, b, delta_x;

    a = 1.0, b = 1.0, delta_x = 2.0;
    if (fabs(fds_1(b, a, delta_x) - 0.0) >= 0.0001)
        return failure(f_name);

    a = 1.0, b = 3.0;
    if (fabs(fds_1(b, a, delta_x) - 1.0) >= 0.0001)
        return failure(f_name);

    a = 3.0, b = 1.0;
    if (fabs(fds_1(b, a, delta_x) + 1.0) >= 0.0001)
        return failure(f_name);

    // TODO: Study divide by zero error

    return success(f_name);
}

int test_compute_mesh()
{
    char *f_name = "compute_mesh";
    run(f_name);

    int n_x = 3, n_y = 3;
    double x_size = 1.0, y_size = 1.0;
    struct Point points[n_x * n_y];

    compute_mesh(points, n_x, n_y, x_size, y_size);

    if (points[0].global_index != 0
        || points[1].global_index != 1
        || points[2].global_index != 2
        || points[3].global_index != 3
        || points[4].global_index != 4
        || points[5].global_index != 5
        || points[6].global_index != 6
        || points[7].global_index != 7
        || points[8].global_index != 8)
        return failure(f_name);

    if (points[0].x_index != 0
        || points[0].y_index != 0
        || points[1].x_index != 1
        || points[1].y_index != 0
        || points[2].x_index != 2
        || points[2].y_index != 0
        || points[3].x_index != 0
        || points[3].y_index != 1
        || points[4].x_index != 1
        || points[4].y_index != 1
        || points[5].x_index != 2
        || points[5].y_index != 1
        || points[6].x_index != 0
        || points[6].y_index != 2
        || points[7].x_index != 1
        || points[7].y_index != 2
        || points[8].x_index != 2
        || points[8].y_index != 2)
        return failure(f_name);

    if (fabs(points[0].x - 0.0) >= 0.0001
        || fabs(points[0].y - 0.0) >= 0.0001
        || fabs(points[1].x - 0.5) >= 0.0001
        || fabs(points[1].y - 0.0) >= 0.0001
        || fabs(points[2].x - 1.0) >= 0.0001
        || fabs(points[2].y - 0.0) >= 0.0001
        || fabs(points[3].x - 0.0) >= 0.0001
        || fabs(points[3].y - 0.5) >= 0.0001
        || fabs(points[4].x - 0.5) >= 0.0001
        || fabs(points[4].y - 0.5) >= 0.0001
        || fabs(points[5].x - 1.0) >= 0.0001
        || fabs(points[5].y - 0.5) >= 0.0001
        || fabs(points[6].x - 0.0) >= 0.0001
        || fabs(points[6].y - 1.0) >= 0.0001
        || fabs(points[7].x - 0.5) >= 0.0001
        || fabs(points[7].y - 1.0) >= 0.0001
        || fabs(points[8].x - 1.0) >= 0.0001
        || fabs(points[8].y - 1.0) >= 0.0001)
        return failure(f_name);

    return success(f_name);
}

int test_set_diffusivities()
{
    char *f_name = "set_diffusivities";
    run(f_name);

    int n_x = 3, n_y = 3;
    double x_size = 1.0, y_size = 1.0;
    int length = n_x * n_y;
    struct Point points[length];
    double diff_1 = 1.0, diff_2 = 2.0;

    compute_mesh(points, n_x, n_y, x_size, y_size);

    set_diffusivities(points, length, diff_1, diff_1, 0.0, 0.0, 0.0, 0.0);
    for (int k = 0; k < length; k++) {
        if (fabs(points[k].diffusivity - 1.0) >= 0.0001)
            return failure(f_name);
    }

    set_diffusivities(points, length, diff_1, diff_2, 0.0, x_size, 0.0, y_size);
    for (int k = 0; k < length; k++) {
        if (fabs(points[k].diffusivity - 2.0) >= 0.0001)
            return failure(f_name);
    }

    set_diffusivities(points, length, diff_1, diff_2, 0.25, 0.75, 0.25, 0.75);
    if (fabs(points[0].diffusivity - 1.0) >= 0.0001
        || fabs(points[1].diffusivity - 2.0) >= 0.0001
        || fabs(points[2].diffusivity - 1.0) >= 0.0001
        || fabs(points[3].diffusivity - 1.0) >= 0.0001
        || fabs(points[4].diffusivity - 2.0) >= 0.0001
        || fabs(points[5].diffusivity - 1.0) >= 0.0001
        || fabs(points[6].diffusivity - 1.0) >= 0.0001
        || fabs(points[7].diffusivity - 2.0) >= 0.0001
        || fabs(points[8].diffusivity - 1.0) >= 0.0001)
        return failure(f_name);

    return success(f_name);
}

int test_init_temperatures()
{
    char *f_name = "init_temperatures";
    run(f_name);

    int n_x = 3, n_y = 3;
    int length = n_x * n_y;
    struct Point points[length];
    double temp = 273.0;

    init_temperatures(points, length, temp);

    for (int k = 0; k < length; k++) {
        if (fabs(points[k].temperature - 273.0) >= 0.0001)
            return failure(f_name);
    }

    return success(f_name);
}

int test_compute_step()
{
    char *f_name = "compute_step";
    run(f_name);

    int n_x = 5, n_y = 5;
    double x_size = 1.0, y_size = 1.0;
    int length = n_x * n_y;
    struct Point points[length];
    double diff = 1e-5, temp = 273.0;
    double d_t = 0.1;

    compute_mesh(points, n_x, n_y, x_size, y_size);

    // No boundary conditions
    set_diffusivities(points, length, diff, diff, 0.0, x_size, 0.0, y_size);
    init_temperatures(points, length, temp);

    compute_step(points, n_x, n_y, x_size, y_size, d_t, 0.5, 0.5, 273.0);
    for (int k = 0; k < length; k++) {
        if (fabs(points[k].temperature - 273.0) >= 0.0001)
            return failure(f_name);
    }

    // Boundary condition of 500K at the center
    // TODO: Test for the general case, not only for n_x = 5, n_y = 5
    for (int iter = 0; iter < 1000; iter++) {
        compute_step(points, n_x, n_y, x_size, y_size, d_t, 0.5, 0.5, 500.0);
    }
    // for (int k = 0; k < length; k++) {
    //     printf("Temperature[%d] = %f\n", k, points[k].temperature);
    // }
    for (int k = 0; k < 6; k++) {
        if (fabs(points[k].temperature - 273.0) >= 0.0001)
            return failure(f_name);
    }
    for (int k = 6; k < 9; k++) {
        if (fabs(points[k].temperature - 273.0) <= 0.0001)
            return failure(f_name);
    }
    for (int k = 9; k < 11; k++) {
        if (fabs(points[k].temperature - 273.0) >= 0.0001)
            return failure(f_name);
    }
    for (int k = 11; k < 14; k++) {
        if (fabs(points[k].temperature - 273.0) <= 0.0001)
            return failure(f_name);
    }
    for (int k = 14; k < 16; k++) {
        if (fabs(points[k].temperature - 273.0) >= 0.0001)
            return failure(f_name);
    }
    for (int k = 16; k < 19; k++) {
        if (fabs(points[k].temperature - 273.0) <= 0.0001)
            return failure(f_name);
    }
    for (int k = 19; k < length; k++) {
        if (fabs(points[k].temperature - 273.0) >= 0.0001)
            return failure(f_name);
    }

    return success(f_name);
}

int test_solve_diffusion()
{
    char *f_name = "solve_diffusion";
    run(f_name);

    int n_x = 5, n_y = 5;
    double x_size = 1.0, y_size = 1.0;
    int length = n_x * n_y;
    struct Point points[length];
    double d_t = 0.1;

    solve_diffusion(0, points, n_x, n_y, x_size, y_size, d_t,
                    273.0, 0.5, 0.5, 500.0);
    for (int k = 0; k < 6; k++) {
        if (fabs(points[k].temperature - 273.0) >= 0.0001)
            return failure(f_name);
    }
    for (int k = 6; k < 9; k++) {
        if (fabs(points[k].temperature - 273.0) <= 0.0001)
            return failure(f_name);
    }
    for (int k = 9; k < 11; k++) {
        if (fabs(points[k].temperature - 273.0) >= 0.0001)
            return failure(f_name);
    }
    for (int k = 11; k < 14; k++) {
        if (fabs(points[k].temperature - 273.0) <= 0.0001)
            return failure(f_name);
    }
    for (int k = 14; k < 16; k++) {
        if (fabs(points[k].temperature - 273.0) >= 0.0001)
            return failure(f_name);
    }
    for (int k = 16; k < 19; k++) {
        if (fabs(points[k].temperature - 273.0) <= 0.0001)
            return failure(f_name);
    }
    for (int k = 19; k < length; k++) {
        if (fabs(points[k].temperature - 273.0) >= 0.0001)
            return failure(f_name);
    }

    return success(f_name);
}

void run(char *file_name)
{
    printf("%s[ RUN      ] ", KGRN);
    printf("%s%s()\n", KNRM, file_name);
}

int success(char *file_name)
{
    printf("%s[       OK ] ", KGRN);
    printf("%s%s()\n", KNRM, file_name);
    return EXIT_SUCCESS;
}

int failure(char *file_name)
{
    printf("%s[  FAILED  ] ", KRED);
    printf("%s%s()\n", KNRM, file_name);
    return EXIT_FAILURE;
}
