#include "pybind11.hpp"

void labelled_submodule(pybind11::module& module);

void labelled_module(pybind11::module& module) {
    labelled_submodule(module);
}
