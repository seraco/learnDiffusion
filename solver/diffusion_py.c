#include <Python.h>
#include <stdio.h>
#include <stdlib.h>

#include "diffusion.h"

const double TOTAL_TIME = 1.0;
const double DIFF_1 = 1.5e-9;
const double DIFF_2 = 3e-9;
const double DIFF_3 = 1.5e-10;

static PyObject *solver(PyObject *self, PyObject *args);

static PyMethodDef FooMethods[] = {
    {"solve",  solver, METH_VARARGS},
    {NULL, NULL}  /* Sentinel */
};

void initdiffusion(void)
{
    (void) Py_InitModule("diffusion", FooMethods);
}

static PyObject *solver(PyObject *self, PyObject *args)
{
    double init_val, source_val, x_perc_bc, y_perc_bc;

    if (!PyArg_ParseTuple(args, "dddd", &init_val, &x_perc_bc, &y_perc_bc,
                          &source_val))
        return NULL;

    int n_x, n_y;
    read_png_file("../img/segmentation_bw.png", &n_x, &n_y);

    int length = n_x * n_y;
    struct Point *points = (struct Point*)malloc(sizeof(struct Point) * length);
    int iter;

    iter = solve_diffusion(0, points, n_x, n_y, TOTAL_TIME,
                           init_val, x_perc_bc, y_perc_bc, source_val,
                           DIFF_1, DIFF_2, DIFF_3);

    return Py_BuildValue("I", iter);
}
