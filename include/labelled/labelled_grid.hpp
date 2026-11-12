/***************************************************************************
 *            labelled/labelled_grid.hpp
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

/** @file labelled/labelled_grid.hpp
 *  @brief Grids and pavings with named coordinate spaces.
 */
#ifndef ARIADNE_REASONING_LABELLED_GRID_HPP
#define ARIADNE_REASONING_LABELLED_GRID_HPP
#include <utility>

#include "function/function.hpp"
#include "paving/binary_tree_paving.hpp"
#include "paving/paving_interface.hpp"
#include "symbolic/identifier.hpp"
#include "symbolic/space.hpp"
#include "utility/container.hpp"

namespace Ariadne {

/** @brief LabelledGrid: grids and pavings with named coordinate spaces. */
struct LabelledGrid {
    template<class SYS>
    explicit LabelledGrid(SYS const& system)
        : LabelledGrid(Grid(system.state_space().dimension()), system.state_space()) {}
    LabelledGrid(const Grid& grid, const RealSpace& space)
        : _grid(grid), _variables(space.variable_names()) {}

    /** @brief Return the underlying grid. */
    const Grid& euclidean_grid() const { return this->_grid; }
    /** @brief Return the corresponding named variable space. */
    const RealSpace space() const { return RealSpace(this->_variables); }

    /** @brief Write or compare labelled objects. */
    friend OutputStream& operator<<(OutputStream& os, const LabelledGrid& grid) {
        return os << "LabelledGrid( " << grid._grid << ", " << grid._variables << ")";
    }

  private:
    Grid _grid;
    List<Identifier> _variables;
};

// Representation-neutral paving: the concrete backend is selected once
// when the Paving value is supplied, and retained by subsequent operations.
struct LabelledPaving {
  public:
    LabelledPaving(Paving paving, const RealSpace& space)
        : _set(std::move(paving)), _variables(space.variable_names()) {
        ARIADNE_PRECONDITION(_set.dimension() == space.dimension());
    }
    LabelledPaving(const Grid& grid, const RealSpace& space)
        : LabelledPaving(Paving(new BinaryTreePaving(grid)), space) {}
    explicit LabelledPaving(const LabelledGrid& grid)
        : LabelledPaving(grid.euclidean_grid(), grid.space()) {}

    /** @brief Access the underlying Euclidean representation. */
    Paving& euclidean_set() { return _set; }
    /** @brief Access the underlying Euclidean representation. */
    const Paving& euclidean_set() const { return _set; }
    /** @brief Return the corresponding named variable space. */
    RealSpace space() const { return RealSpace(_variables); }

  private:
    Paving _set;
    List<Identifier> _variables;
};

/** @brief LabelledBinaryTreePaving: grids and pavings with named coordinate spaces. */
struct LabelledBinaryTreePaving {
  public:
    LabelledBinaryTreePaving(const Grid& grid, const RealSpace& space)
        : _set(grid), _variables(space.variable_names()) {}
    LabelledBinaryTreePaving(BinaryTreePaving set, const RealSpace& space)
        : _set(set), _variables(space.variable_names()) {}
    explicit LabelledBinaryTreePaving(const LabelledGrid& lgrid)
        : LabelledBinaryTreePaving(lgrid.euclidean_grid(), lgrid.space()) {}
    /** @brief Access the underlying Euclidean representation. */
    BinaryTreePaving& euclidean_set() { return this->_set; }
    /** @brief Access the underlying Euclidean representation. */
    const BinaryTreePaving& euclidean_set() const { return this->_set; }
    /** @brief Return the corresponding named variable space. */
    const RealSpace space() const { return RealSpace(this->_variables); }

  private:
    BinaryTreePaving _set;
    List<Identifier> _variables;
};

/** @brief LabelledStateAuxiliaryGrid: grids and pavings with named coordinate spaces. */
struct LabelledStateAuxiliaryGrid {
    template<class SYS>
    explicit LabelledStateAuxiliaryGrid(SYS const& system)
        : LabelledStateAuxiliaryGrid(Grid(system.state_space().dimension()), system.state_space(),
                                     system.auxiliary_mapping(), system.auxiliary_space()) {}
    /** @brief Construct or operate on the labelled geometric object. */
    LabelledStateAuxiliaryGrid(const Grid& grid, const RealSpace& state_space);
    LabelledStateAuxiliaryGrid(const Grid& grid, const RealSpace& state_space,
                               const EffectiveVectorMultivariateFunction& auxiliary_mapping, const RealSpace& auxiliary_space)
        : _grid(grid), _auxiliary_mapping(auxiliary_mapping), _state_variables(state_space.variable_names()), _auxiliary_variables(auxiliary_space.variable_names()) {}

    /** @brief Return the underlying grid. */
    const Grid& euclidean_grid() const { return this->_grid; }
    /** @brief Return the associated function or mapping. */
    const EffectiveVectorMultivariateFunction& auxiliary_mapping() const { return this->_auxiliary_mapping; }
    /** @brief Return the corresponding named variable space. */
    const RealSpace state_space() const { return RealSpace(this->_state_variables); }
    /** @brief Return the corresponding named variable space. */
    const RealSpace auxiliary_space() const { return RealSpace(this->_auxiliary_variables); }

    /** @brief Write or compare labelled objects. */
    friend OutputStream& operator<<(OutputStream& os, const LabelledStateAuxiliaryGrid& grid) {
        return os << "LabelledStateAuxiliaryGrid( " << grid._grid << ", " << grid._state_variables << ", "
                  << grid._auxiliary_mapping << ", " << grid._auxiliary_variables << ")";
    }

  private:
    Grid _grid;
    EffectiveVectorMultivariateFunction _auxiliary_mapping;
    List<Identifier> _state_variables;
    List<Identifier> _auxiliary_variables;
};

} // namespace Ariadne
#endif // ARIADNE_REASONING_LABELLED_GRID_HPP
