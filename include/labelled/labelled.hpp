/***************************************************************************
 *            labelled/labelled.hpp
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

/** @file labelled/labelled.hpp
 *  @brief Named variable spaces attached to geometric objects.
 */

#ifndef ARIADNE_LABELLED_LABELLED_HPP
#define ARIADNE_LABELLED_LABELLED_HPP

#include "symbolic/space.hpp"

namespace Ariadne {

/** @brief Labelled: named variable spaces attached to geometric objects. */
class Labelled {
  public:
    /** @brief Return the corresponding named variable space. */
    explicit Labelled(RealSpace const& space) : _space(space) { }

    /** @brief Return the corresponding named variable space. */
    RealSpace const& space() const { return _space; }
    /** @brief Return the corresponding named variable space. */
    Set<RealVariable> variables() const { return _space.variables(); }

  protected:
    RealSpace _space;
};

} // namespace Ariadne

#endif
