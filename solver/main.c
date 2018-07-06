#include <stdlib.h>
#include <stdio.h>

#include "diffusion.h"

const int N_X = 257;
const int N_Y = 257;
const double X_SIZE = 1.0;
const double Y_SIZE = 1.0;

int main()
{
    int length = N_X * N_Y;
    struct Point points[length];
    double d_t = 0.3, init_temp = 273.0;
    double diff_1 = 1e-5, diff_2 = 2e-5;

    solve_diffusion(1, points, N_X, N_Y, X_SIZE, Y_SIZE, d_t,
                    init_temp, 0.5, 0.5, 500.0,
                    diff_1, diff_2, 0.25, 0.75, 0.25, 0.75);

    return EXIT_SUCCESS;
}
