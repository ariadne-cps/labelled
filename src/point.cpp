/***************************************************************************
 *            src/point.cpp
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

/** @file src/point.cpp
 *  @brief Instantiate labelled point types.
 */

#include "labelled/point.tpl.hpp"

namespace Ariadne {

template<>
String class_name<LabelledPoint<Real>>() { return "LabelledPoint<Real>"; }
template<>
String class_name<LabelledPoint<FloatDPApproximation>>() { return "LabelledPoint<FloatDPApproximation>"; }

template class LabelledPoint<Real>;
template class LabelledPoint<FloatDPApproximation>;

} // namespace Ariadne
