#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "diffusion.h"

// #define KYEL "\x1B[33m"
#define KGRN "\x1B[32m"
#define KRED "\x1B[31m"
#define KNRM "\x1B[0m"

int test_cds_2();
int test_compute_mesh();
void run(char *file_name);
int success(char *file_name);
int failure(char *file_name);

int main()
{
    if (test_cds_2()
        || test_compute_mesh())
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
