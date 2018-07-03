#include <Python.h>
#include <stdio.h>
#include <stdlib.h>

#include "diffusion.h"

// const int N_X = 256;
// const int N_Y = 256;
// const double X_SIZE = 1.0;
// const double Y_SIZE = 1.0;
// const double D_T = 0.3;
// const double INIT_TEMP = 273.0;

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
    int n_x, n_y;
    double x_size, y_size, d_t, init_temp;

    if (!PyArg_ParseTuple(args, "iidddd", &n_x, &n_y, &x_size, &y_size,
                          &d_t, &init_temp))
        return NULL;

    int length = n_x * n_y;
    struct Point points[length];
    int iter;

    iter = solve_diffusion(1, points, n_x, n_y, x_size, y_size, d_t, init_temp);

    return Py_BuildValue("I", iter);
}
