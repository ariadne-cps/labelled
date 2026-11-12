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

#include "pybind11.hpp"
#include "function-utilities.hpp"

#include "geometry/box.hpp"
#include "labelled/figure.hpp"
#include "labelled/set.hpp"

using namespace Ariadne;

void export_labelled(pybind11::module& module) {
    static constexpr auto reference_internal = pybind11::return_value_policy::reference_internal;

    pybind11::class_<Variables2d> variables2d_class(module,"Variables2d");
    variables2d_class.def(pybind11::init<RealVariable,RealVariable>());
    variables2d_class.def("x", &Variables2d::x);
    variables2d_class.def("y", &Variables2d::y);

    module.def("projection",&projection);

    pybind11::class_<Axes2d> axes2d_class(module,"Axes2d");
    axes2d_class.def(pybind11::init<double,RealVariable,double,double,RealVariable,double>());
    axes2d_class.def(pybind11::init<Real,RealVariable,Real,Real,RealVariable,Real>());

    using LabelledRealBox = LabelledBox<RealInterval>;
    pybind11::class_<LabelledRealBox> labelled_real_box_class(module,"LabelledRealBox");
    labelled_real_box_class.def(pybind11::init<RealSpace,RealBox>());
    labelled_real_box_class.def("dimension", &LabelledRealBox::dimension);
    labelled_real_box_class.def("__str__", &__cstr__<LabelledRealBox>);
    labelled_real_box_class.def("__repr__", &__cstr__<LabelledRealBox>);

    using LabelledFloatDPUpperBox = LabelledBox<FloatDPUpperInterval>;
    pybind11::class_<LabelledFloatDPUpperBox> labelled_floatdp_upper_box_class(module,"LabelledFloatDPUpperBox");
    labelled_floatdp_upper_box_class.def("__getitem__", &LabelledFloatDPUpperBox::operator[]);
    labelled_floatdp_upper_box_class.def("__str__", &__cstr__<LabelledFloatDPUpperBox>);

    pybind11::class_<LabelledFigure> labelled_figure_class(module,"LabelledFigure");
    labelled_figure_class.def(pybind11::init<Axes2d>());
    labelled_figure_class.def("set_axes",(Void(LabelledFigure::*)(const Axes2d&)) &LabelledFigure::set_axes, reference_internal);
    labelled_figure_class.def("properties",(RenderingProperties&(LabelledFigure::*)())&LabelledFigure::properties, reference_internal);
    labelled_figure_class.def("draw",(LabelledFigure&(LabelledFigure::*)(const LabelledDrawable2dInterface&))&LabelledFigure::draw, reference_internal);
    labelled_figure_class.def("draw", [](LabelledFigure& fig, LabelledRealBox const& box) -> LabelledFigure& {
        LabelledDrawableWrapper<RealBox> wrapper(box);
        return fig.draw(wrapper);
    }, reference_internal);
    labelled_figure_class.def("clear",&LabelledFigure::clear, reference_internal);
    labelled_figure_class.def("set_animated", &LabelledFigure::set_animated, reference_internal);
    labelled_figure_class.def("write",(Void(LabelledFigure::*)(const Char*)const)&LabelledFigure::write);
    labelled_figure_class.def("write",(Void(LabelledFigure::*)(const Char*,Nat,Nat)const)&LabelledFigure::write);
}
