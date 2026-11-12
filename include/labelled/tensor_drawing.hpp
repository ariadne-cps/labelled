/***************************************************************************
 *            labelled/tensor_drawing.hpp
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
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Ariadne Labelled.  If not, see <https://www.gnu.org/licenses/>.
 */

/** @file labelled/tensor_drawing.hpp
 *  @brief Drawing adapters for rank-two tensors.
 */

#ifndef ARIADNE_LABELLED_TENSOR_DRAWING_HPP
#define ARIADNE_LABELLED_TENSOR_DRAWING_HPP


#include "algebra/tensor.hpp"
#include "numeric/floatdp.hpp"
#include "numeric/floatmp.hpp"
#include "labelled/figure.hpp"
#include "labelled/graphics_interface.hpp"

namespace Ariadne {

template<SizeType N, class PR>
/** @brief TensorDrawable: drawing adapters for rank-two tensors. */
class TensorDrawable
    : public LabelledDrawable2dInterface
    , public Drawable2dInterface
{
    static_assert(N == 2u, "TensorDrawable supports rank-2 tensors only.");

    using X = Float<PR>;
    Tensor<N,X> _tensor;

  public:
    explicit TensorDrawable(Tensor<N,X> const& tensor) : _tensor(tensor) { }

    /** @brief Create a copy of the labelled drawable. */
    TensorDrawable* clone() const override { return new TensorDrawable(*this); }
    /** @brief Create a copy of the labelled drawable. */
    TensorDrawable* labelled_clone() const override { return new TensorDrawable(*this); }

    /** @brief Return the object's dimension. */
    DimensionType dimension() const override { return _tensor.rank(); }

    /** @brief Render the object in the selected coordinate system. */
    Void draw(CanvasInterface& canvas, Projection2d const&) const override {
        this->_draw_rank2(canvas);
    }

    /** @brief Render the object in the selected coordinate system. */
    Void draw(CanvasInterface& canvas, Variables2d const&) const override {
        this->_draw_rank2(canvas);
    }

  private:
    /** @brief Construct or operate on the labelled geometric object. */
    Void _draw_rank2(CanvasInterface& canvas) const {
        for (SizeType frame=0; frame!=_tensor.size(1); ++frame) {
            canvas.move_to(0.0, _tensor[{0,frame}].get_d());
            for (SizeType i=1; i!=_tensor.size(0); ++i) {
                canvas.line_to(numeric_cast<double>(i), _tensor[{i,frame}].get_d());
            }
            canvas.fill();
        }
    }

};

template<SizeType N, class PR>
/** @brief Construct or operate on the labelled geometric object. */
TensorDrawable<N,PR> tensor_drawable(Tensor<N,Float<PR>> const& tensor) {
    return TensorDrawable<N,PR>(tensor);
}

} // namespace Ariadne

#endif // ARIADNE_LABELLED_TENSOR_DRAWING_HPP
