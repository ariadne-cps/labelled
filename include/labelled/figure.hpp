/***************************************************************************
 *            labelled/figure.hpp
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

/** @file labelled/figure.hpp
 *  @brief Labelled figures, axes and drawing operations.
 */

#ifndef ARIADNE_LABELLED_FIGURE_HPP
#define ARIADNE_LABELLED_FIGURE_HPP

#include "ariadne-drawing.hpp"
#include "labelled/graphics_interface.hpp"
#include "symbolic/variable.hpp"
#include "symbolic/space.hpp"
#include "expression-set/expression_set.hpp"
#include "labelled/set.hpp"

namespace Ariadne {

// Preserve the coordinate interval type used by the labelled API.
using ApproximateDoubleInterval = Interval<ApproximateDouble>;
using ApproximateDoubleVariableInterval = VariableInterval<ApproximateDouble>;
using DoubleVariableInterval = VariableInterval<Double>;

/** @brief Variables2d: labelled figures, axes and drawing operations. */
struct Variables2d {
    Identifier _x,_y;
    Variables2d(const RealVariable& x, const RealVariable& y);
    /** @brief Return this coordinate variable. */
    RealVariable x() const;
    /** @brief Return this coordinate variable. */
    RealVariable y() const;
};

/** @brief Axes2d: labelled figures, axes and drawing operations. */
struct Axes2d {
    Axes2d(const ApproximateDoubleVariableInterval x, const ApproximateDoubleVariableInterval& y);
    Axes2d(ApproximateDouble xl, const RealVariable& x, ApproximateDouble xu,
           ApproximateDouble yl, const RealVariable& y, ApproximateDouble yu);
    Variables2d variables;
    Map<RealVariable,ApproximateDoubleInterval> bounds;
};

/** @brief Project coordinates into the requested variable space. */
Projection2d projection(const RealSpace& space, const Variables2d& variables);

/** @brief LabelledFigure: labelled figures, axes and drawing operations. */
class LabelledFigure {
  public:
    ~LabelledFigure();

    /** @brief Construct or operate on the labelled geometric object. */
    LabelledFigure(const Axes2d& axes);
    /** @brief Construct or operate on the labelled geometric object. */
    LabelledFigure(const Variables2d& vars, VariablesBox<ApproximateIntervalType> const& bnds);

    /** @brief Update the figure axes or bounds. */
    Void set_axes(const Axes2d& axes);
    /** @brief Update the figure axes or bounds. */
    Void set_bounds(const RealVariable& x, const ApproximateDoubleInterval& ivl);
    /** @brief Update the figure axes or bounds. */
    Void set_bounds(const Map<RealVariable,ApproximateDoubleInterval>& b);
    /** @brief Update the figure axes or bounds. */
    Void set_bounding_box(VariablesBox<ApproximateIntervalType> const& bnds);

    /** @brief Access the figure rendering properties. */
    RenderingProperties& properties();
    /** @brief Access the figure rendering properties. */
    RenderingProperties const& properties() const;

    /** @brief Render the object in the selected coordinate system. */
    LabelledFigure& draw(const LabelledDrawable2dInterface& shape);
    /** @brief Clear the labelled figure. */
    LabelledFigure& clear();
    /** @brief Configure animation for the figure. */
    LabelledFigure& set_animated(Bool b);

    /** @brief Write the rendered figure to a file. */
    Void write(const Char* filename, Nat nx, Nat ny) const;
    /** @brief Write the rendered figure to a file. */
    Void write(const Char* filename) const;

    /** @brief Render the object in the selected coordinate system. */
    Void _paint_all(CanvasInterface& canvas) const;

  public:
    struct Data;
  private:
    Data* _data;
};

/** @brief Render the object in the selected coordinate system. */
Void draw(LabelledFigure& fig, const LabelledDrawable2dInterface& shape);
/** @brief Write or compare labelled objects. */
LabelledFigure& operator<<(LabelledFigure& fig, const LabelledDrawable2dInterface& shape);

inline LabelledFigure& operator<<(LabelledFigure& g, const LineStyle& ls) { g.properties().set_line_style(ls); return g; }
inline LabelledFigure& operator<<(LabelledFigure& g, const LineWidth& lw) { g.properties().set_line_width(lw); return g; }
inline LabelledFigure& operator<<(LabelledFigure& g, const LineColour& lc) { g.properties().set_line_colour(lc); return g; }
inline LabelledFigure& operator<<(LabelledFigure& g, const FillStyle& fs) { g.properties().set_fill_style(fs); return g; }
inline LabelledFigure& operator<<(LabelledFigure& g, const FillOpacity& fo) { g.properties().set_fill_opacity(fo); return g; }
inline LabelledFigure& operator<<(LabelledFigure& g, const FillColour& fc) { g.properties().set_fill_colour(fc); return g; }
inline LabelledFigure& operator<<(LabelledFigure& g, const Animated& animation) { g.properties().set_animated(animation); return g; }

template<class S> class LabelledDrawableWrapper : public LabelledDrawable2dInterface {
    LabelledSet<S> _lset;
  public:
    LabelledDrawableWrapper(LabelledSet<S> lset) : _lset(lset) { }
    /** @brief Create a copy of the labelled drawable. */
    LabelledDrawableWrapper<S>* labelled_clone() const override { return new LabelledDrawableWrapper<S>(*this); }
    /** @brief Render the object in the selected coordinate system. */
    Void draw(CanvasInterface& cnvs, Variables2d const& vars) const override {
        Projection2d prj(this->_lset.euclidean_set().dimension(),
                         this->_lset.space()[vars.x()],this->_lset.space()[vars.y()]);
        Ariadne::draw(cnvs,prj,this->_lset.euclidean_set());
    }
};

/** @brief Write or compare labelled objects. */
template<class S> inline LabelledFigure& operator<<(LabelledFigure& g, const LabelledSet<S>& lset) {
    return g << LabelledDrawableWrapper<S>(lset);
}

} // namespace Ariadne

#endif
