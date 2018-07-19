#include <Python.h>
#include <stdio.h>
#include <stdlib.h>

#include "diffusion.h"

const int N_X = 256;
const int N_Y = 256;
const double TOTAL_TIME = 1.0;
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
    double init_temp, i_bc, j_bc, source_val, i_1, i_2, j_1, j_2;

    if (!PyArg_ParseTuple(args, "diidiiii", &init_temp, &i_bc, &j_bc, &source_val,
                          &i_1, &i_2, &j_1, &j_2))
        return NULL;

    int length = N_X * N_Y;
    struct Point points[length];
    int iter;

    iter = solve_diffusion(0, points, N_X, N_Y, TOTAL_TIME, init_temp,
                           i_bc, j_bc, source_val, DIFF_1, DIFF_2,
                           i_1, i_2, j_1, j_2);

    return Py_BuildValue("I", iter);
}
