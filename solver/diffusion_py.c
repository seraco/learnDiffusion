#include <Python.h>
#include <stdio.h>
#include <stdlib.h>

#include "diffusion.h"

const int N_X = 256;
const int N_Y = 256;
const double X_SIZE = 1.0;
const double Y_SIZE = 1.0;
const double D_T = 0.7;
// const double INIT_TEMP = 273.0;
const double DIFF_1 = 1e-5;
const double DIFF_2 = 2e-5;

static PyObject *solver(PyObject *self, PyObject *args);

static PyMethodDef FooMethods[] = {
    {"solve",  solver, METH_VARARGS},
    {NULL, NULL}  /* Sentinel */
};

void initdiffusion()
{
    (void) Py_InitModule("diffusion", FooMethods);
}

static PyObject *solver(PyObject *self, PyObject *args)
{
    double init_temp, x_bc, y_bc, temp_bc, x_1, x_2, y_1, y_2;

    if (!PyArg_ParseTuple(args, "dddddddd", &init_temp, &x_bc, &y_bc, &temp_bc,
                          &x_1, &x_2, &y_1, &y_2))
        return NULL;

    int length = N_X * N_Y;
    struct Point points[length];
    int iter;

    iter = solve_diffusion(1, points, N_X, N_Y, X_SIZE, Y_SIZE, D_T, init_temp,
                           x_bc, y_bc, temp_bc, DIFF_1, DIFF_2,
                           x_1, x_2, y_1, y_2);

    return Py_BuildValue("I", iter);
}
