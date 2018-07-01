#include <stdlib.h>
#include <stdio.h>

#include "diffusion.h"

const int N_X = 256;
const int N_Y = 256;

int main()
{
    printf("Nx = %d, Ny = %d\n", N_X, N_Y);

    double b = 3.0, a = 1.0, delta_x = 2.0;
    printf("CDS2 = %f\n", cds_2(b, a, delta_x));

    return EXIT_SUCCESS;
}
