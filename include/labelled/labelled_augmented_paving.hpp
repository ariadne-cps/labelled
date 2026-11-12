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
#include "paving/augmented_paving.hpp"
#include "labelled/labelled_grid.hpp"
#include "labelled/labelled_mapping.hpp"

namespace Ariadne {

/** @brief LabelledAugmentedPaving: augmented pavings with labelled state and auxiliary variables. */
class LabelledAugmentedPaving
    : public AugmentedPaving
{
    /** @brief Construct or operate on the labelled geometric object. */
    template<class SYS> static LabelledMapping labelled_auxiliary_mapping(SYS const& sys) {
        return LabelledMapping(sys.state_space(),sys.auxiliary_mapping(),sys.auxiliary_space()); }
  public:
    typedef LabelledGrid GridType;

    LabelledAugmentedPaving(Grid const& grid, RealSpace const& state_space,
                    Mapping const& auxiliary_mapping, RealSpace const& auxiliary_space);
    LabelledAugmentedPaving(BinaryTreePaving const& paving, RealSpace const& state_space,
                    Mapping const& auxiliary_mapping, RealSpace const& auxiliary_space);
    //! Preserve the selected Paving implementation (Tree or ROBDD).
    LabelledAugmentedPaving(Paving const& paving, RealSpace const& state_space,
                    Mapping const& auxiliary_mapping, RealSpace const& auxiliary_space);

    LabelledAugmentedPaving(Grid const& grid, LabelledMapping const& auxiliary)
        : LabelledAugmentedPaving(BinaryTreePaving(grid),auxiliary) { }
    LabelledAugmentedPaving(BinaryTreePaving const& paving, LabelledMapping const& auxiliary)
        : LabelledAugmentedPaving(paving,auxiliary.argument_space(),auxiliary.mapping(),auxiliary.result_space()) { }
    LabelledAugmentedPaving(Paving const& paving, LabelledMapping const& auxiliary)
        : LabelledAugmentedPaving(paving,auxiliary.argument_space(),auxiliary.mapping(),auxiliary.result_space()) { }
    LabelledAugmentedPaving(LabelledGrid const& grid, LabelledMapping const& auxiliary)
        : LabelledAugmentedPaving(grid.euclidean_grid(),auxiliary) { ARIADNE_PRECONDITION(grid.space()==auxiliary.argument_space()); }
    LabelledAugmentedPaving(LabelledBinaryTreePaving const& paving, LabelledMapping const& auxiliary)
        : LabelledAugmentedPaving(paving.euclidean_set(),auxiliary) { ARIADNE_PRECONDITION(paving.space()==auxiliary.argument_space()); }

    template<class SYS> LabelledAugmentedPaving(Grid const& grid, SYS const& system)
        : LabelledAugmentedPaving(grid,system.state_space(),system.auxiliary_mapping(),system.auxiliary_space()) { }
    template<class SYS> LabelledAugmentedPaving(BinaryTreePaving const& paving, SYS const& system)
        : LabelledAugmentedPaving(paving,system.state_space(),system.auxiliary_mapping(),system.auxiliary_space()) { }
    template<class SYS> LabelledAugmentedPaving(Paving const& paving, SYS const& system)
        : LabelledAugmentedPaving(paving,system.state_space(),system.auxiliary_mapping(),system.auxiliary_space()) { }
    template<class SYS> LabelledAugmentedPaving(LabelledGrid const& grid, SYS const& system)
        : LabelledAugmentedPaving(grid.euclidean_grid(),system.state_space(),system.auxiliary_mapping(),system.auxiliary_space()) {
            ARIADNE_PRECONDITION(grid.space()==system.state_space()); }
    template<class SYS> LabelledAugmentedPaving(LabelledBinaryTreePaving const& paving, SYS const& system)
        : LabelledAugmentedPaving(paving.euclidean_set(),system.state_space(),system.auxiliary_mapping(),system.auxiliary_space()) {
            ARIADNE_PRECONDITION(paving.space()==system.state_space()); }

    /** @brief Access the underlying Euclidean representation. */
    AugmentedPaving& euclidean_set() { return *this; }
    /** @brief Access the underlying Euclidean representation. */
    AugmentedPaving const& euclidean_set() const { return *this; }
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
    Void adjoin(LabelledAugmentedPaving const& other) {
        ARIADNE_PRECONDITION(this->_state_variables==other._state_variables);
        this->state_paving().adjoin(static_cast<PavingInterface const&>(other.state_paving())); }
    /** @brief Apply the requested set operation. */
    Void restrict(LabelledAugmentedPaving const& other) {
        ARIADNE_PRECONDITION(this->_state_variables==other._state_variables);
        this->state_paving().restrict(static_cast<PavingInterface const&>(other.state_paving())); }
    /** @brief Apply the requested set operation. */
    Void remove(LabelledAugmentedPaving const& other) {
        ARIADNE_PRECONDITION(this->_state_variables==other._state_variables);
        this->state_paving().remove(static_cast<PavingInterface const&>(other.state_paving())); }

    /** @brief Apply the requested set operation. */
    friend Bool subset(LabelledAugmentedPaving const& set1, LabelledAugmentedPaving const& set2) {
        ARIADNE_PRECONDITION(set1._state_variables==set2._state_variables);
        return set1.state_paving().subset(static_cast<PavingInterface const&>(set2.state_paving())); }
    /** @brief Apply the requested set operation. */
    friend Bool intersect(LabelledAugmentedPaving const& set1, LabelledAugmentedPaving const& set2) {
        ARIADNE_PRECONDITION(set1._state_variables==set2._state_variables);
        return set1.state_paving().intersects(static_cast<PavingInterface const&>(set2.state_paving())); }

    /** @brief Create a copy of the labelled drawable. */
    virtual LabelledAugmentedPaving* clone() const override { return new LabelledAugmentedPaving(*this); }

    /** @brief Write or compare labelled objects. */
    friend OutputStream& operator<<(OutputStream& os, LabelledAugmentedPaving const& set) {
        return os << "LabelledAugmentedPaving(" << set.state_paving() << ", state_variables=" << set._state_variables << ", auxiliary_mapping=" << set.auxiliary_mapping().function() << ", auxiliary_variables=" << set._auxiliary_variables << ")"; }

  private:
    List<Identifier> _state_variables;
    List<Identifier> _auxiliary_variables;
};

/** @brief Construct or operate on the labelled geometric object. */
LabelledBinaryTreePaving inner_approximation(EffectiveEuclideanSetInterface const& set, LabelledGrid const& grid, Nat fineness);

} // namespace Ariadne
#endif // ARIADNE_REASONING_LABELLED_AUGMENTED_PAVING_HPP
