/***************************************************************************
 *            labelled/curve.hpp
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

/** @file labelled/curve.hpp
 *  @brief Labelled interpolation curves with coordinate-aware drawing.
 */

#ifndef ARIADNE_LABELLED_CURVE_HPP
#define ARIADNE_LABELLED_CURVE_HPP

#include "set/curve.hpp"
#include "labelled/point.hpp"

namespace Ariadne {

/** @brief LabelledInterpolatedCurve: labelled interpolation curves with coordinate-aware drawing. */
class LabelledInterpolatedCurve
    : public LabelledDrawable2dInterface,
      public InterpolatedCurve,
      public Labelled
{
  public:
    typedef LabelledPoint<FloatDPApproximation> PointType;

    /** @brief Construct or operate on the labelled geometric object. */
    explicit LabelledInterpolatedCurve(const PointType& pt);

    /** @brief Create a copy of the labelled drawable. */
    LabelledInterpolatedCurve* labelled_clone() const override;

    /** @brief Render the object in the selected coordinate system. */
    Void draw(CanvasInterface&, const Variables2d&) const override;
};

} // namespace Ariadne

#endif
