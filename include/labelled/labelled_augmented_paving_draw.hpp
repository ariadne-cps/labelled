/***************************************************************************
 *            labelled/labelled_augmented_paving_draw.hpp
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

/** @file labelled/labelled_augmented_paving_draw.hpp
 *  @brief Drawing adapters for labelled augmented pavings.
 */

// Temporary adapter; final home will be the drawing repository.
#ifndef ARIADNE_REASONING_LABELLED_AUGMENTED_PAVING_DRAW_HPP
#define ARIADNE_REASONING_LABELLED_AUGMENTED_PAVING_DRAW_HPP

#include "drawing/augmented_paving_draw.hpp"
#include "labelled/figure.hpp"
#include "labelled/labelled_augmented_paving.hpp"

namespace Ariadne {

/** @brief Render the object in the selected coordinate system. */
inline Void draw(CanvasInterface& canvas, const Variables2d& axes, const LabelledAugmentedPaving& paving) {
    /** @brief Project coordinates into the requested variable space. */
    Projection2d proj = Ariadne::projection(paving.state_auxiliary_space(), axes);
    Ariadne::draw(canvas, proj, static_cast<const AugmentedPaving&>(paving));
}

/** @brief LabelledAugmentedPavingDrawable: drawing adapters for labelled augmented pavings. */
class LabelledAugmentedPavingDrawable final : public LabelledDrawable2dInterface {
  public:
    /** @brief Construct a LabelledAugmentedPavingDrawable instance. */
    explicit LabelledAugmentedPavingDrawable(const LabelledAugmentedPaving& paving) : _paving(paving) {}
    /** @brief Create a copy of the labelled drawable. */
    LabelledAugmentedPavingDrawable* labelled_clone() const override {
        return new LabelledAugmentedPavingDrawable(*this);
    }
    /** @brief Render the object in the selected coordinate system. */
    Void draw(CanvasInterface& canvas, const Variables2d& axes) const override {
        Ariadne::draw(canvas, axes, _paving);
    }

  private:
    LabelledAugmentedPaving _paving;
};

// Projection-based figures use the same auxiliary graph as AugmentedPaving.
// A dedicated overload avoids reliance on implicit conversions or on
// mathematical types inheriting rendering interfaces.
inline Void draw_to_figure(Figure& figure, const LabelledAugmentedPaving& paving) {
    draw_to_figure(figure, static_cast<const AugmentedPaving&>(paving));
}
/** @brief Render the object in the selected coordinate system. */
inline Void draw(Figure& figure, const LabelledAugmentedPaving& paving) {
    /** @brief Perform the labelled geometric operation. */
    draw_to_figure(figure, paving);
}
/** @brief Write or compare labelled objects. */
inline Figure& operator<<(Figure& figure, const LabelledAugmentedPaving& paving) {
    /** @brief Perform the labelled geometric operation. */
    draw_to_figure(figure, paving);
    return figure;
}

/** @brief Render the object in the selected coordinate system. */
inline Void draw_to_figure(LabelledFigure& figure, const LabelledAugmentedPaving& paving) {
    figure.draw(LabelledAugmentedPavingDrawable(paving));
}
/** @brief Render the object in the selected coordinate system. */
inline Void draw(LabelledFigure& figure, const LabelledAugmentedPaving& paving) {
    /** @brief Perform the labelled geometric operation. */
    draw_to_figure(figure, paving);
}
/** @brief Write or compare labelled objects. */
inline LabelledFigure& operator<<(LabelledFigure& figure, const LabelledAugmentedPaving& paving) {
    /** @brief Perform the labelled geometric operation. */
    draw_to_figure(figure, paving);
    return figure;
}

} // namespace Ariadne
#endif // ARIADNE_REASONING_LABELLED_AUGMENTED_PAVING_DRAW_HPP
