/***************************************************************************
 *            python/bindings/labelled_submodule.cpp
 *
 *  Copyright  2026  Luca Geretti
 *
 ****************************************************************************/

/*
 *  This file is part of Ariadne Labelled.
 *
 *  Ariadne Labelled is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Ariadne Labelled is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Ariadne Labelled. If not, see <https://www.gnu.org/licenses/>.
 */

/** @file python/bindings/labelled_submodule.cpp
 *  @brief Export labelled types and operations to Python.
 */

#include "pybind11.hpp"

void export_labelled(pybind11::module& module);

void labelled_submodule(pybind11::module& module) {
    export_labelled(module);
}

void export_labelled(pybind11::module& module) {
    // The labelled graphics and set adapters now live in the Drawing module;
    // the labelled core is header-only and has no Python-visible classes here.
    (void)module;
}
