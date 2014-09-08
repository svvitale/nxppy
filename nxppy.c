#include <Python.h>
#include "Mifare.h"

/*###########################################################
# Python Extension definitions
###########################################################*/
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

PyObject *
PyInit_nxppy(void)

#else
#define INITERROR return

void
initnxppy(void)
#endif
{
    PyObject *module;

    MifareType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&MifareType) < 0) {
        return NULL;
    }

#if PY_MAJOR_VERSION >= 3
    module = PyModule_Create(&moduledef);
#else
    module = Py_InitModule("nxppy", nxppy_methods);
#endif

    if (module == NULL)
        INITERROR;

    Py_INCREF(&MifareType);
    PyModule_AddObject(module, "Mifare", (PyObject *)&MifareType);

#if PY_MAJOR_VERSION >= 3
    return module;
#endif
}
