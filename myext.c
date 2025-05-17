#include <Python.h>

static PyObject* myext_hello(PyObject* self, PyObject* args) {
    return Py_BuildValue("s", "Hello from C Extension!");
}

static PyMethodDef MyExtMethods[] = {
    {"hello", myext_hello, METH_VARARGS, "Returns a greeting string."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef myextmodule = {
    PyModuleDef_HEAD_INIT,
    "myext",
    NULL,
    -1,
    MyExtMethods
};

PyMODINIT_FUNC PyInit_myext(void) {
    return PyModule_Create(&myextmodule);
}
