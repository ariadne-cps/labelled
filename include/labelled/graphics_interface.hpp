/***************************************************************************
 *            labelled/graphics_interface.hpp
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

/** @file labelled/graphics_interface.hpp
 *  @brief Interface for drawing objects in labelled coordinates.
 */

#ifndef ARIADNE_LABELLED_GRAPHICS_INTERFACE_HPP
#define ARIADNE_LABELLED_GRAPHICS_INTERFACE_HPP

#include "rendering/rendering_interface.hpp"

namespace Ariadne {

/** @brief Variables2d: interface for drawing objects in labelled coordinates. */
struct Variables2d;

/** @brief LabelledDrawable2dInterface: interface for drawing objects in labelled coordinates. */
class LabelledDrawable2dInterface {
  public:
    /** @brief Construct or operate on the labelled geometric object. */
    virtual ~LabelledDrawable2dInterface() = default;
    /** @brief Create a copy of the labelled drawable. */
    virtual LabelledDrawable2dInterface* labelled_clone() const = 0;
    /** @brief Render the object in the selected coordinate system. */
    virtual Void draw(CanvasInterface& c, const Variables2d& p) const = 0;
};

} // namespace Ariadne

#endif
