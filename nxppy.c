#include <Python.h>
#include "main.h"

static PyObject *NxpError;

static PyObject *nxppy_GetUID(PyObject *self)
{
    const char *command;
    int sts = 0;
    main(0, 0);
    return PyLong_FromLong(sts);
}

static PyMethodDef NxppyMethods[] = {
    {"GetUID",  nxppy_GetUID, METH_VARARGS, "Get the UID of the card currently present on the reader."},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC
initnxppy(void)
{
    PyObject *m = Py_InitModule("nxppy", NxppyMethods);

    if (m == NULL)
        return;

    NxpError = PyErr_NewException("nxppy.error", NULL, NULL);
    Py_INCREF(NxpError);
    PyModule_AddObject(m, "error", NxpError);
}
