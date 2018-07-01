#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "diffusion.h"

#define KYEL "\x1B[33m"
#define KGRN "\x1B[32m"
#define KRED "\x1B[31m"

int test_cds_2();
int success();
int failure();

int main()
{
    if (test_cds_2())
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

int test_cds_2()
{
    printf("%sTesting cds_2() ... ", KYEL);

    double a, b, delta_x;

    a = 1.0, b = 1.0, delta_x = 2.0;
    // printf("%f\n", cds_2(b, a, delta_x));
    if (fabs(cds_2(b, a, delta_x) - 0.0) >= 0.0001)
        return failure();

    a = 1.0, b = 3.0;
    // printf("%f\n", cds_2(b, a, delta_x));
    if (fabs(cds_2(b, a, delta_x) - 0.5) >= 0.0001)
        return failure();

    a = 3.0, b = 1.0;
    // printf("%f\n", cds_2(b, a, delta_x));
    if (fabs(cds_2(b, a, delta_x) + 0.5) >= 0.0001)
        return failure();

    // TODO: Study divide by zero error
    return success();
}

int success()
{
    printf("%sSuccess\n", KGRN);
    return EXIT_SUCCESS;
}

int failure()
{
    printf("%sFailure\n", KRED);
    return EXIT_FAILURE;
}
