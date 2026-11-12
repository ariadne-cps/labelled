/***************************************************************************
 *            src/curve.cpp
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

/** @file src/curve.cpp
 *  @brief Implement labelled curves and their drawing adapters.
 */

#include "labelled/curve.hpp"
#include "labelled/figure.hpp"

namespace Ariadne {

LabelledInterpolatedCurve::LabelledInterpolatedCurve(const PointType& pt)
    : InterpolatedCurve(CurveInterface::PointType(pt)), Labelled(pt.space()) { }

LabelledInterpolatedCurve* LabelledInterpolatedCurve::labelled_clone() const {
    return new LabelledInterpolatedCurve(*this);
}

Void LabelledInterpolatedCurve::draw(CanvasInterface& c, const Variables2d& v) const {
    Projection2d proj=projection(this->space(),v);
    Ariadne::draw(c,proj,static_cast<InterpolatedCurve const&>(*this));
}

} // namespace Ariadne
