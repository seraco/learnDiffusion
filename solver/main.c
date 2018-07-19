#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "diffusion.h"

const int N_X = 257;
const int N_Y = 257;

int main()
{
    int length = N_X * N_Y;
    struct Point points[length];
    double total_time = 1.0;
    double init_temp = 0.0, source = 1e5;
    double diff_1 = 1.5e-5, diff_2 = 3e-5;

    solve_diffusion(1, points, N_X, N_Y, total_time,
                    init_temp, 128, 128, source,
                    diff_1, diff_2,
                    64, 192, 64, 192);

    return EXIT_SUCCESS;
}
