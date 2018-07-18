#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "diffusion.h"

const int N_X = 256;
const int N_Y = 256;

int main()
{
    int length = N_X * N_Y;
    struct Point points[length];
    double d_t, total_time = 1.0;
    double init_temp = 0.0, max_temp = 1.0;
    double diff_1 = 1.5e-5, diff_2 = 3e-5;
    double side_size, middle, first_quarter, third_quarter;
    double delta_space;

    side_size = sqrt(2 * diff_2 * total_time);
    middle = side_size / 2.0;
    first_quarter = side_size / 4.0;
    third_quarter = first_quarter * 3.0;

    delta_space = side_size / (N_X - 1);
    d_t = 0.25 * delta_space * delta_space / diff_2;
    d_t *= 0.98;

    printf("Side size = %f, Delta time = %f\n", side_size, d_t);

    solve_diffusion(1, points, N_X, N_Y, side_size, side_size, d_t,
                    init_temp, middle, middle, max_temp,
                    diff_1, diff_2,
                    first_quarter, third_quarter, first_quarter, third_quarter);

    return EXIT_SUCCESS;
}
