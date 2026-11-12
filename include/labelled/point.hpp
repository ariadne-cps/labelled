/***************************************************************************
 *            labelled/point.hpp
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

/** @file labelled/point.hpp
 *  @brief Points with named variables and labelled drawing support.
 */

#ifndef ARIADNE_LABELLED_POINT_HPP
#define ARIADNE_LABELLED_POINT_HPP

#include "geometry/point.hpp"
#include "symbolic/identifier.hpp"
#include "symbolic/space.hpp"
#include "symbolic/assignment.hpp"
#include "labelled/labelled.hpp"
#include "labelled/graphics_interface.hpp"
#include "labelled/figure.hpp"

namespace Ariadne {

template<class X> class LabelledPoint;

using LabelledRealPoint = LabelledPoint<Real>;
template<class IVL> class LabelledBox;
using LabelledExactBoxType = LabelledBox<ExactIntervalType>;

template<class X>
/** @brief LabelledPoint: points with named variables and labelled drawing support. */
class LabelledPoint : public LabelledDrawable2dInterface, public Point<X>, public Labelled {
  public:
    /** @brief Construct or operate on the labelled geometric object. */
    LabelledPoint(RealSpace const& state_space, Point<X> const& pt);
    /** @brief Construct or operate on the labelled geometric object. */
    LabelledPoint(List<Assignment<RealVariable,X>> const& val);
    /** @brief Construct or operate on the labelled geometric object. */
    LabelledPoint(InitializerList<Assignment<RealVariable,X>> const& val);
    template<class T> requires Convertible<T,X>
    /** @brief Return the corresponding named variable space. */
    LabelledPoint(const LabelledPoint<T>& pt) : Point<X>(pt), Labelled(pt.space()) { }
    template<class Y, class... PRS> requires Constructible<X,Y,PRS...>
    /** @brief Return the corresponding named variable space. */
    LabelledPoint(const LabelledPoint<Y>& pt, PRS... prs) : Point<X>(pt,prs...), Labelled(pt.space()) { }

    /** @brief Create a copy of the labelled drawable. */
    LabelledPoint* labelled_clone() const override;
    /** @brief Render the object in the selected coordinate system. */
    Void draw(CanvasInterface&, const Variables2d&) const override;
};

/** @brief Project coordinates into the requested variable space. */
template<class X> inline LabelledPoint<X> project(LabelledPoint<X> const& pt, Variables2d const& v) {
    /** @brief Project coordinates into the requested variable space. */
    Projection2d p = projection(pt.space(),v);
    return LabelledPoint<X>(pt.space(),project(static_cast<Point<X> const&>(pt),p));
}

} // namespace Ariadne

#endif
