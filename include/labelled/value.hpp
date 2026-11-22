/***************************************************************************
 *            labelled/value.hpp
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

/** @file labelled/value.hpp
 *  @brief Representation-independent values carrying coordinate metadata.
 */

#ifndef ARIADNE_LABELLED_VALUE_HPP
#define ARIADNE_LABELLED_VALUE_HPP

#include <concepts>
#include <utility>

#include "symbolic/space.hpp"
#include "utility/macros.hpp"

namespace Ariadne {

// Transitional name: the existing non-template Labelled base class must be
// migrated before the generic wrapper can take the public name Labelled<T>.
// This type intentionally has no dependency on sets, paving or drawing.
template<class T, class Metadata = RealSpace>
class LabelledValue {
    T _value;
    Metadata _metadata;

  public:
    using ValueType = T;
    using MetadataType = Metadata;

    LabelledValue(T value, Metadata metadata)
        : _value(std::move(value)), _metadata(std::move(metadata)) {
        if constexpr (std::same_as<Metadata, RealSpace> &&
                      requires(const T& v) { v.dimension(); }) {
            ARIADNE_PRECONDITION(_metadata.dimension() == _value.dimension());
        }
    }

    const T& value() const { return _value; }
    T& value() { return _value; }

    const Metadata& labels() const { return _metadata; }

    const RealSpace& space() const
        requires std::same_as<Metadata, RealSpace> {
        return _metadata;
    }

    auto variables() const
        requires requires(const Metadata& labels) { labels.variables(); } {
        return _metadata.variables();
    }
};

} // namespace Ariadne

#endif // ARIADNE_LABELLED_VALUE_HPP
