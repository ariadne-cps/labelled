#include "pybind11.hpp"

void labelling_submodule(pybind11::module& module);

void labelling_module(pybind11::module& module) {
    labelling_submodule(module);
}
