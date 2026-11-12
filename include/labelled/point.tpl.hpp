/***************************************************************************
 *            labelled/point.tpl.hpp
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

/** @file labelled/point.tpl.hpp
 *  @brief Template definitions for labelled points.
 */

#ifndef ARIADNE_LABELLED_POINT_TPL_HPP
#define ARIADNE_LABELLED_POINT_TPL_HPP

#include "labelled/point.hpp"

namespace Ariadne {

template<class X>
LabelledPoint<X>::LabelledPoint(const RealSpace& state_space, const Point<X>& pt)
    : Point<X>(pt), Labelled(state_space) {}

template<class X>
LabelledPoint<X>::LabelledPoint(const List<Assignment<RealVariable, X>>& x)
    : Point<X>(x.size(), [&x](SizeType i) { return x[i].right_hand_side(); }),
      Labelled(RealSpace(left_hand_sides(x))) {}

template<class X>
LabelledPoint<X>::LabelledPoint(const InitializerList<Assignment<RealVariable, X>>& x)
    : LabelledPoint<X>(List<Assignment<RealVariable, X>>(x)) {}

/** @brief Create a copy of the labelled drawable. */
template<class X>
LabelledPoint<X>* LabelledPoint<X>::labelled_clone() const {
    return new LabelledPoint(*this);
}

/** @brief Render the object in the selected coordinate system. */
template<class X>
Void LabelledPoint<X>::draw(CanvasInterface& canvas, const Variables2d& axes) const {
    /** @brief Project coordinates into the requested variable space. */
    Projection2d proj = projection(this->space(), axes);
    Ariadne::draw(canvas, proj, static_cast<const Point<X>&>(*this));
}

} // namespace Ariadne

#endif
