#include <Python.h>
#include "Mifare.h"

#define UID_BUFFER_SIZE 10
#define UID_ASCII_BUFFER_SIZE ((UID_BUFFER_SIZE * 2) + 1)

static phbalReg_R_Pi_spi_DataParams_t balReader;
static phhalHw_Rc523_DataParams_t hal;
static uint8_t initialized = false;

static PyObject *nxppy_read_mifare(PyObject *self, PyObject *args)
{
    if (!initialized) {
        init(&balReader, &hal);
        initialized = true;
    }

    uint8_t byteBufferSize = UID_BUFFER_SIZE;
    uint8_t byteBuffer[UID_BUFFER_SIZE];

    char asciiBuffer[UID_ASCII_BUFFER_SIZE];

    if (DetectMifare(&hal, byteBuffer, &byteBufferSize) == 0) {
        /* reset the IC  */
        readerIC_Cmd_SoftReset(&hal);

        uint8_t i;

        if (byteBufferSize + 1 > UID_ASCII_BUFFER_SIZE) {
            // Truncate if we got back too much data
            byteBufferSize = UID_ASCII_BUFFER_SIZE - 1;
        }

        for (i = 0; i < byteBufferSize; i++) {
            sprintf(&asciiBuffer[2 * i], "%02X", byteBuffer[i]);
        }

        return PyUnicode_FromString(asciiBuffer);
    }

    Py_RETURN_NONE;
}

/*###########################################################
# Python Extension definitions
###########################################################*/
static PyMethodDef nxppy_methods[] = {
    {"read_mifare",  nxppy_read_mifare, METH_VARARGS, "Get the UID of the card currently present on the reader."},
    {NULL, NULL}
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "nxppy",
    NULL,
    0,
    nxppy_methods,
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
#if PY_MAJOR_VERSION >= 3
    PyObject *module = PyModule_Create(&moduledef);
#else
    PyObject *module = Py_InitModule("nxppy", nxppy_methods);
#endif

    if (module == NULL)
        INITERROR;

#if PY_MAJOR_VERSION >= 3
    return module;
#endif
}
