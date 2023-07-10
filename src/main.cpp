#include <pybind11/cast.h>
#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>

#include "cppygen_generated.hpp"

PYBIND11_MODULE(pygentest, m) { CPPyGen::CPPyGenExport(m); }
