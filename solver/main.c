#include <stdlib.h>
#include <stdio.h>

#include "diffusion.h"

const int N_X = 5;
const int N_Y = 5;
const double X_SIZE = 1.0;
const double Y_SIZE = 1.0;

int main()
{
    int length = N_X * N_Y;
    struct Point points[length];
    double d_t = 0.3, init_temp = 273.0;

    solve_diffusion(1, points, N_X, N_Y, X_SIZE, Y_SIZE, d_t, init_temp);

    return EXIT_SUCCESS;
}
