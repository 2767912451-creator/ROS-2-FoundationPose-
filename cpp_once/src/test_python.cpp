#include <Python.h>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>
#include <iostream>

int main() {
    std::cout << "Step 1: before Py_SetPythonHome" << std::endl;
    Py_SetPythonHome(Py_DecodeLocale("/home/ckh/anaconda3/envs/foundationpose", nullptr));

    std::cout << "Step 2: before Py_Initialize" << std::endl;
    Py_Initialize();

    std::cout << "Step 3: before _import_array" << std::endl;
    if (_import_array() < 0) {
        PyErr_Print();
        std::cerr << "NumPy init failed" << std::endl;
        return 1;
    }

    std::cout << "Step 4: all OK, finalizing" << std::endl;
    Py_Finalize();
    std::cout << "Done." << std::endl;
    return 0;
}
