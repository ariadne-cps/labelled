/***************************************************************************
 *            labelled/set.hpp
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

/** @file labelled/set.hpp
 *  @brief Euclidean sets carrying named coordinate spaces.
 */

#ifndef ARIADNE_LABELLED_SET_HPP
#define ARIADNE_LABELLED_SET_HPP

#include "labelled/graphics_interface.hpp"
#include "labelled/labelled.hpp"

#include "expression-set/expression_set.hpp"

namespace Ariadne {

//! \brief A set formed by labelled the variables of a Euclidean set of type \a S.
template<class S>
class LabelledSet : public Labelled {
    S _set;

  public:
    typedef S EuclideanSetType;

    /** @brief Return the number of dimensions. */
    LabelledSet(const RealSpace& spc, const EuclideanSetType& set) : Labelled(spc), _set(set) { ARIADNE_ASSERT_MSG(spc.dimension() == set.dimension(), "spc=" << spc << ", set.dimension()=" << set.dimension()); }
    template<class X>
        requires Same<S, Point<X>>
    explicit LabelledSet(const VariablesPoint<X>& point)
        : Labelled(RealSpace(List<RealVariable>(point.variables()))), _set(point.euclidean_set(this->space())) {}
    template<class IVL>
        requires Same<S, Box<IVL>>
    explicit LabelledSet(const VariablesBox<IVL>& box)
        : Labelled(RealSpace(List<RealVariable>(box.variables()))), _set(box.euclidean_set(this->space())) {}
    /** @brief Access the underlying Euclidean representation. */
    const EuclideanSetType& continuous_set() const { return this->_set; }
    /** @brief Access the underlying Euclidean representation. */
    const EuclideanSetType& euclidean_set() const { return this->_set; }
    /** @brief Access the underlying Euclidean representation. */
    EuclideanSetType& euclidean_set() { return this->_set; }
    /** @brief Return the underlying Euclidean set or its bounds. */
    EuclideanSetType euclidean_set(const RealSpace& vars) const {
        Array<SizeType> prj(vars.dimension());
        for (SizeType i = 0; i != vars.dimension(); ++i) {
            prj[i] = this->space().index(vars.variable(i));
        }
        return project(this->_set, prj);
    }
    /** @brief Access the underlying Euclidean representation. */
    DimensionType dimension() const { return this->euclidean_set().dimension(); }
    /** @brief Apply the requested set operation. */
    template<class T>
    Void adjoin(const LabelledSet<T>& other) const {
        ARIADNE_ASSERT(this->space() == other.space());
        this->euclidean_set().adjoin(other.euclidean_set());
    }
    decltype(auto) bounding_box() const { return LabelledSet(this->space(), this->euclidean_set().bounding_box()); }
    decltype(auto) bounding_boxes() const { return LabelledSet(this->space(), this->euclidean_set().bounding_boxes()); }
    /** @brief Render the object in the selected coordinate system. */
    Void draw(CanvasInterface& cnvs, const Variables2d& vars) const;

    /** @brief Apply the requested set operation. */
    template<class E>
    friend decltype(auto) widen(const LabelledSet<S>& set, const E& e) {
        return LabelledSet(set.space(), widen(set.euclidean_set(), e));
    }
    /** @brief Write or compare labelled objects. */
    friend OutputStream& operator<<(OutputStream& os, const LabelledSet<S>& eset) {
        return os << "LabelledSet( space=" << eset.space() << ", set=" << eset.continuous_set() << " )";
    }
};
/** @brief Construct or operate on the labelled geometric object. */
template<class S>
LabelledSet(const RealSpace&, const S&) -> LabelledSet<S>;

template<class IVL>
class LabelledBox : public LabelledSet<Box<IVL>> {
  public:
    /** @brief Return the corresponding coordinate. */
    LabelledBox(const RealSpace& spc, const Box<IVL>& set) : LabelledSet<Box<IVL>>(spc, set) {}
    IVL operator[](const RealVariable& v) const { return this->euclidean_set()[this->space().index(v)]; }
};

/** @brief Write or compare labelled objects. */
template<class S>
EqualsType<S> operator==(const LabelledSet<S>& eset1, const LabelledSet<S>& eset2) {
    if (eset1.variables() != eset2.variables()) {
        return false;
    }
    ARIADNE_ASSERT(eset1.space() == eset2.space());
    return eset1.euclidean_set() == eset2.euclidean_set();
}

template<class UB>
using LabelledInterval = VariableInterval<UB>;
template<class BS>
using LabelledListSet = LabelledSet<ListSet<BS>>;

} // namespace Ariadne

#endif
