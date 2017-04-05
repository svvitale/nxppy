#include <Python.h>
#include "Mifare.h"

PyObject *InitError;
PyObject *SelectError;
PyObject *ReadError;
PyObject *WriteError;
PyObject *AuthError;

/*
 * ########################################################### # Python Extension definitions
 * ###########################################################
 */
#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "nxppy",
    NULL,
    0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

#define INITERROR return NULL

PyObject *PyInit_nxppy(void)
#else
#define INITERROR return

PyMethodDef nxppy_methods[] = {
    {NULL, NULL}
    ,
};

void initnxppy(void)
#endif
{
    PyObject *module;

    MifareType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&MifareType) < 0) {
#if PY_MAJOR_VERSION >= 3
        return NULL;
#else
        return;
#endif
    }
#if PY_MAJOR_VERSION >= 3
    module = PyModule_Create(&moduledef);
#else
    module = Py_InitModule("nxppy", nxppy_methods);
#endif

    if (module == NULL)
        INITERROR;

    Py_INCREF(&MifareType);
    PyModule_AddObject(module, "Mifare", (PyObject *) & MifareType);

    InitError = PyErr_NewException("nxppy.InitError", NULL, NULL);
    Py_INCREF(InitError);
    PyModule_AddObject(module, "InitError", InitError);

    SelectError = PyErr_NewException("nxppy.SelectError", NULL, NULL);
    Py_INCREF(SelectError);
    PyModule_AddObject(module, "SelectError", SelectError);

    ReadError = PyErr_NewException("nxppy.ReadError", NULL, NULL);
    Py_INCREF(ReadError);
    PyModule_AddObject(module, "ReadError", ReadError);

    WriteError = PyErr_NewException("nxppy.WriteError", NULL, NULL);
    Py_INCREF(WriteError);
    PyModule_AddObject(module, "WriteError", WriteError);

    AuthError = PyErr_NewException("nxppy.AuthError", NULL, NULL);
    Py_INCREF(AuthError);
    PyModule_AddObject(module, "AuthError", AuthError);

#if PY_MAJOR_VERSION >= 3
    return module;
#endif
}
