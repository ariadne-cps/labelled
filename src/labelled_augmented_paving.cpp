/***************************************************************************
 *            src/labelled_augmented_paving.cpp
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

/** @file src/labelled_augmented_paving.cpp
 *  @brief Implement labelled augmented paving operations.
 */

// Labelled augmented paving and labelled grid operations.
#include "labelled/labelled_augmented_paving.hpp"

namespace Ariadne {

LabelledAugmentedPaving::LabelledAugmentedPaving(Grid const& grid,
                                 RealSpace const& state_space,
                                 EffectiveVectorMultivariateFunction const& auxiliary_mapping,
                                 RealSpace const& auxiliary_space)
    : LabelledAugmentedPaving(BinaryTreePaving(grid), state_space, auxiliary_mapping, auxiliary_space) { }

LabelledAugmentedPaving::LabelledAugmentedPaving(BinaryTreePaving const& paving,
                                 RealSpace const& state_space,
                                 EffectiveVectorMultivariateFunction const& auxiliary_mapping,
                                 RealSpace const& auxiliary_space)
    : LabelledAugmentedPaving(Paving(new BinaryTreePaving(paving)),
                             state_space,auxiliary_mapping,auxiliary_space) { }

LabelledAugmentedPaving::LabelledAugmentedPaving(Paving const& paving,
                                 RealSpace const& state_space,
                                 EffectiveVectorMultivariateFunction const& auxiliary_mapping,
                                 RealSpace const& auxiliary_space)
    : AugmentedPaving(paving,auxiliary_mapping)
    , _state_variables(state_space.variable_names())
    , _auxiliary_variables(auxiliary_space.variable_names())
{
    ARIADNE_PRECONDITION(paving.dimension()==state_space.dimension());
}


LabelledBinaryTreePaving inner_approximation(EffectiveEuclideanSetInterface const& set, LabelledGrid const& grid, Nat fineness) {
    LabelledBinaryTreePaving paving(grid); paving.euclidean_set().adjoin_inner_approximation(set,fineness); return paving;
}

const RealSpace LabelledAugmentedPaving::state_space() const {
    return RealSpace(this->_state_variables);
}

const RealSpace LabelledAugmentedPaving::auxiliary_space() const {
    return RealSpace(this->_auxiliary_variables);
}

const RealSpace LabelledAugmentedPaving::state_auxiliary_space() const {
    return join(this->state_space(),this->auxiliary_space());
}

const LabelledGrid LabelledAugmentedPaving::grid() const {
    return LabelledGrid(this->euclidean_set().grid(),this->state_space());
}

const Mapping LabelledAugmentedPaving::auxiliary_function() const {
    return this->AugmentedPaving::auxiliary_mapping();
}

const LabelledMapping LabelledAugmentedPaving::auxiliary_mapping() const {
    return LabelledMapping(this->state_space(), this->auxiliary_function(), this->auxiliary_space());
}

const LabelledMapping LabelledAugmentedPaving::auxiliary_data() const {
    return this->auxiliary_mapping();
}


} // namespace Ariadne
