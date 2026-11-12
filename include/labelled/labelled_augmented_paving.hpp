/***************************************************************************
 *            labelled/labelled_augmented_paving.hpp
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

/** @file labelled/labelled_augmented_paving.hpp
 *  @brief Augmented pavings with labelled state and auxiliary variables.
 */
#ifndef ARIADNE_REASONING_LABELLED_AUGMENTED_PAVING_HPP
#define ARIADNE_REASONING_LABELLED_AUGMENTED_PAVING_HPP
#include "labelled/labelled_grid.hpp"
#include "labelled/labelled_mapping.hpp"
#include "paving/augmented_paving.hpp"

namespace Ariadne {

/** @brief LabelledAugmentedPaving: augmented pavings with labelled state and auxiliary variables. */
class LabelledAugmentedPaving
    : public AugmentedPaving {
    /** @brief Construct or operate on the labelled geometric object. */
    template<class SYS>
    static LabelledMapping labelled_auxiliary_mapping(SYS const& sys) {
        return LabelledMapping(sys.state_space(), sys.auxiliary_mapping(), sys.auxiliary_space());
    }

  public:
    typedef LabelledGrid GridType;

    LabelledAugmentedPaving(const Grid& grid, const RealSpace& state_space,
                            const Mapping& auxiliary_mapping, const RealSpace& auxiliary_space);
    LabelledAugmentedPaving(const BinaryTreePaving& paving, const RealSpace& state_space,
                            const Mapping& auxiliary_mapping, const RealSpace& auxiliary_space);
    //! Preserve the selected Paving implementation (Tree or ROBDD).
    LabelledAugmentedPaving(const Paving& paving, const RealSpace& state_space,
                            const Mapping& auxiliary_mapping, const RealSpace& auxiliary_space);

    LabelledAugmentedPaving(const Grid& grid, const LabelledMapping& auxiliary)
        : LabelledAugmentedPaving(BinaryTreePaving(grid), auxiliary) {}
    LabelledAugmentedPaving(const BinaryTreePaving& paving, const LabelledMapping& auxiliary)
        : LabelledAugmentedPaving(paving, auxiliary.argument_space(), auxiliary.mapping(), auxiliary.result_space()) {}
    LabelledAugmentedPaving(const Paving& paving, const LabelledMapping& auxiliary)
        : LabelledAugmentedPaving(paving, auxiliary.argument_space(), auxiliary.mapping(), auxiliary.result_space()) {}
    LabelledAugmentedPaving(const LabelledGrid& grid, const LabelledMapping& auxiliary)
        : LabelledAugmentedPaving(grid.euclidean_grid(), auxiliary) { ARIADNE_PRECONDITION(grid.space() == auxiliary.argument_space()); }
    LabelledAugmentedPaving(const LabelledBinaryTreePaving& paving, const LabelledMapping& auxiliary)
        : LabelledAugmentedPaving(paving.euclidean_set(), auxiliary) { ARIADNE_PRECONDITION(paving.space() == auxiliary.argument_space()); }

    template<class SYS>
    LabelledAugmentedPaving(const Grid& grid, SYS const& system)
        : LabelledAugmentedPaving(grid, system.state_space(), system.auxiliary_mapping(), system.auxiliary_space()) {}
    template<class SYS>
    LabelledAugmentedPaving(const BinaryTreePaving& paving, SYS const& system)
        : LabelledAugmentedPaving(paving, system.state_space(), system.auxiliary_mapping(), system.auxiliary_space()) {}
    template<class SYS>
    LabelledAugmentedPaving(const Paving& paving, SYS const& system)
        : LabelledAugmentedPaving(paving, system.state_space(), system.auxiliary_mapping(), system.auxiliary_space()) {}
    template<class SYS>
    LabelledAugmentedPaving(const LabelledGrid& grid, SYS const& system)
        : LabelledAugmentedPaving(grid.euclidean_grid(), system.state_space(), system.auxiliary_mapping(), system.auxiliary_space()) {
        ARIADNE_PRECONDITION(grid.space() == system.state_space());
    }
    template<class SYS>
    LabelledAugmentedPaving(const LabelledBinaryTreePaving& paving, SYS const& system)
        : LabelledAugmentedPaving(paving.euclidean_set(), system.state_space(), system.auxiliary_mapping(), system.auxiliary_space()) {
        ARIADNE_PRECONDITION(paving.space() == system.state_space());
    }

    /** @brief Access the underlying Euclidean representation. */
    AugmentedPaving& euclidean_set() { return *this; }
    /** @brief Access the underlying Euclidean representation. */
    const AugmentedPaving& euclidean_set() const { return *this; }
    /** @brief Return the associated named variable space. */
    const RealSpace state_space() const;
    /** @brief Return the associated named variable space. */
    const RealSpace auxiliary_space() const;
    /** @brief Construct or operate on the labelled geometric object. */
    const RealSpace state_auxiliary_space() const;

    /** @brief Return the underlying grid. */
    const LabelledGrid grid() const;
    /** @brief Return the associated mapping. */
    const LabelledMapping auxiliary_data() const;
    /** @brief Return the associated mapping. */
    const LabelledMapping auxiliary_mapping() const;
    /** @brief Return the associated mapping. */
    const Mapping auxiliary_function() const;

    /** @brief Apply the requested set operation. */
    Void adjoin(const LabelledAugmentedPaving& other) {
        ARIADNE_PRECONDITION(this->_state_variables == other._state_variables);
        this->state_paving().adjoin(static_cast<const PavingInterface&>(other.state_paving()));
    }
    /** @brief Apply the requested set operation. */
    Void restrict(const LabelledAugmentedPaving& other) {
        ARIADNE_PRECONDITION(this->_state_variables == other._state_variables);
        this->state_paving().restrict(static_cast<const PavingInterface&>(other.state_paving()));
    }
    /** @brief Apply the requested set operation. */
    Void remove(const LabelledAugmentedPaving& other) {
        ARIADNE_PRECONDITION(this->_state_variables == other._state_variables);
        this->state_paving().remove(static_cast<const PavingInterface&>(other.state_paving()));
    }

    /** @brief Apply the requested set operation. */
    friend Bool subset(const LabelledAugmentedPaving& set1, const LabelledAugmentedPaving& set2) {
        ARIADNE_PRECONDITION(set1._state_variables == set2._state_variables);
        return set1.state_paving().subset(static_cast<const PavingInterface&>(set2.state_paving()));
    }
    /** @brief Apply the requested set operation. */
    friend Bool intersect(const LabelledAugmentedPaving& set1, const LabelledAugmentedPaving& set2) {
        ARIADNE_PRECONDITION(set1._state_variables == set2._state_variables);
        return set1.state_paving().intersects(static_cast<const PavingInterface&>(set2.state_paving()));
    }

    /** @brief Create a copy of the labelled drawable. */
    virtual LabelledAugmentedPaving* clone() const override { return new LabelledAugmentedPaving(*this); }

    /** @brief Write or compare labelled objects. */
    friend OutputStream& operator<<(OutputStream& os, const LabelledAugmentedPaving& set) {
        return os << "LabelledAugmentedPaving(" << set.state_paving() << ", state_variables=" << set._state_variables << ", auxiliary_mapping=" << set.auxiliary_mapping().function() << ", auxiliary_variables=" << set._auxiliary_variables << ")";
    }

  private:
    List<Identifier> _state_variables;
    List<Identifier> _auxiliary_variables;
};

/** @brief Construct or operate on the labelled geometric object. */
LabelledBinaryTreePaving inner_approximation(const EffectiveEuclideanSetInterface& set, const LabelledGrid& grid, Nat fineness);

} // namespace Ariadne
#endif // ARIADNE_REASONING_LABELLED_AUGMENTED_PAVING_HPP
