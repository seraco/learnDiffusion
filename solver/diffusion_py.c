#include <Python.h>
#include <stdio.h>
#include <stdlib.h>

#include "diffusion.h"

const double TOTAL_TIME = 1.0;
const double DIFF_1 = 1.5e-9;
const double DIFF_2 = 3e-9;
const double DIFF_3 = 1.5e-10;

static PyObject *solver(PyObject *self, PyObject *args);

struct module_state {
    PyObject *error;
};

////////////////////////////////////////////////////////////////////////////////
// IF
#if PY_MAJOR_VERSION >= 3
#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
#else
#define GETSTATE(m) (&_state)
static struct module_state _state;
#endif
// ENDIF
////////////////////////////////////////////////////////////////////////////////

static PyMethodDef diffusion_methods[] = {
    {"solve",  solver, METH_VARARGS},
    {NULL, NULL}
};

////////////////////////////////////////////////////////////////////////////////
// IF
#if PY_MAJOR_VERSION >= 3

static int diffusion_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int diffusion_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}

static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "diffusion",
        NULL,
        sizeof(struct module_state),
        diffusion_methods,
        NULL,
        diffusion_traverse,
        diffusion_clear,
        NULL
};

#define INITERROR return NULL

PyMODINIT_FUNC
PyInit_diffusion(void)

#else
#define INITERROR return

void
initdiffusion(void)
#endif
// ENDIF
////////////////////////////////////////////////////////////////////////////////
{
////////////////////////////////////////////////////////////////////////////////
// IF
#if PY_MAJOR_VERSION >= 3
    PyObject *module = PyModule_Create(&moduledef);
#else
    PyObject *module = Py_InitModule("diffusion", diffusion_methods);
#endif
// ENDIF
////////////////////////////////////////////////////////////////////////////////

    if (module == NULL)
        INITERROR;
    struct module_state *st = GETSTATE(module);

    st->error = PyErr_NewException("diffusion.Error", NULL, NULL);
    if (st->error == NULL) {
        Py_DECREF(module);
        INITERROR;
    }

////////////////////////////////////////////////////////////////////////////////
// IF
#if PY_MAJOR_VERSION >= 3
    return module;
#endif
// ENDIF
////////////////////////////////////////////////////////////////////////////////
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
