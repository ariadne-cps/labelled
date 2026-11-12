/***************************************************************************
 *            labelled/labelled_mapping.hpp
 *
 *  Copyright  2011-20  Pieter Collins
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

/** @file labelled/labelled_mapping.hpp
 *  @brief Mappings equipped with argument and result variable spaces.
 */
#ifndef ARIADNE_REASONING_LABELLED_MAPPING_HPP
#define ARIADNE_REASONING_LABELLED_MAPPING_HPP
#include "function/function.hpp"
#include "symbolic/identifier.hpp"
#include "symbolic/space.hpp"
#include "utility/container.hpp"

namespace Ariadne {

/** @brief LabelledMapping: mappings equipped with argument and result variable spaces. */
class LabelledMapping {
  public:
    LabelledMapping(RealSpace argument_space, EffectiveVectorMultivariateFunction mapping, RealSpace result_space)
        : _mapping(mapping), _argument_variables(argument_space.variable_names()), _result_variables(result_space.variable_names()) { }

    /** @brief Return the corresponding named variable space. */
    const RealSpace argument_space() const { return RealSpace(this->_argument_variables); }
    /** @brief Return the associated function or mapping. */
    const EffectiveVectorMultivariateFunction& mapping() const { return this->_mapping; }
    /** @brief Return the associated function or mapping. */
    const EffectiveVectorMultivariateFunction& function() const { return this->_mapping; }
    /** @brief Return the corresponding named variable space. */
    const RealSpace result_space() const { return RealSpace(this->_result_variables); }
  private:
    EffectiveVectorMultivariateFunction _mapping;
    List<Identifier> _argument_variables;
    List<Identifier> _result_variables;
};

} // namespace Ariadne
#endif // ARIADNE_REASONING_LABELLED_MAPPING_HPP
