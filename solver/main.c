#include <stdlib.h>
#include <stdio.h>
#include <png.h>

#include "diffusion.h"

// const int N_X = 5;
// const int N_Y = 3;

int main()
{
    int n_x, n_y;

    read_png_file("../img/segmentation_bw.png", &n_x, &n_y);

    int length = n_x * n_y;
    struct Point *points = (struct Point*)malloc(sizeof(struct Point) * length);
    double total_time = 0.01;
    double init_val = 0.0, source = 1.0; // source val of 1e5
    double diff_1 = 1.5e-9, diff_2 = 3e-9, diff_3 = 1.5e-10;

    solve_diffusion(1, points, n_x, n_y, total_time,
                    init_val, 0.25, 0.5, source,
                    diff_1, diff_2, diff_3);

    return EXIT_SUCCESS;
}
