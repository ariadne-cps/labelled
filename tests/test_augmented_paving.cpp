/***************************************************************************
 *            tests/test_augmented_paving.cpp
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

/** @file tests/test_augmented_paving.cpp
 *  @brief Test labelled augmented paving and grid operations.
 */

#include "labelled/labelled_augmented_paving.hpp"
#include "paving/robdd_paving.hpp"
#include <memory>
#include <sstream>
#include "labelled/labelled_augmented_paving_draw.hpp"
#include "rendering/null_rendering.hpp"
#include "ariadne-testing.hpp"

using namespace Ariadne;

class TestLabelledAugmentedPaving : public Ariadne::Testing::ContextFixture {
  public:
    using ContextFixture::ContextFixture;

    Void test_labelled_grid_and_augmented_operations() {
        RealVariable x("x"),y("y"),z("z"),w("w");
        RealSpace state({x,y}),auxiliary({z}),other_state({x,w});
        Grid grid(2u);
        Mapping mapping({EffectiveScalarMultivariateFunction::coordinate(2u,0u)});
        LabelledMapping labelled(state,mapping,auxiliary);
        struct Description {
            RealSpace states,auxiliaries;
            Mapping function;
            RealSpace state_space() const { return states; }
            RealSpace auxiliary_space() const { return auxiliaries; }
            Mapping auxiliary_mapping() const { return function; }
        } system{state,auxiliary,mapping};
        LabelledGrid labelled_grid(system);
        LabelledBinaryTreePaving tree(labelled_grid);
        LabelledBinaryTreePaving copied_tree(BinaryTreePaving(grid),state);
        LabelledPaving generic(grid,state);
        LabelledPaving from_grid(labelled_grid);
        LabelledStateAuxiliaryGrid augmented_grid(system);
        LabelledStateAuxiliaryGrid const& const_grid=augmented_grid;
        ARIADNE_TESTING_EXPECT_EQUAL(labelled_grid.euclidean_grid(),grid);
        ARIADNE_TESTING_EXPECT_EQUAL(labelled_grid.space(),state);
        ARIADNE_TESTING_EXPECT_EQUAL(tree.space(),state);
        ARIADNE_TESTING_PROVE(copied_tree.euclidean_set().is_empty());
        ARIADNE_TESTING_PROVE(generic.euclidean_set().is_empty());
        LabelledPaving const& const_generic=from_grid;
        ARIADNE_TESTING_PROVE(const_generic.euclidean_set().is_empty());
        ARIADNE_TESTING_EXPECT_EQUAL(const_grid.euclidean_grid(),grid);
        ARIADNE_TESTING_EXPECT_EQUAL(const_grid.state_space(),state);
        ARIADNE_TESTING_EXPECT_EQUAL(const_grid.auxiliary_space(),auxiliary);
        ARIADNE_TESTING_EXPECT_EQUAL(const_grid.auxiliary_mapping().result_size(),1u);
        std::ostringstream text;
        text<<labelled_grid<<augmented_grid;
        ARIADNE_TESTING_PROVE(text.str().find("LabelledStateAuxiliaryGrid")!=std::string::npos);

        GridCell root(grid,0u,BinaryWord{});
        tree.euclidean_set().adjoin(root);
        LabelledBinaryTreePaving const& const_tree=tree;
        ARIADNE_TESTING_PROVE(const_tree.euclidean_set().superset(root));
        LabelledAugmentedPaving first(tree,labelled);
        LabelledAugmentedPaving second(grid,labelled);
        LabelledAugmentedPaving third(Paving(new BinaryTreePaving(grid)),labelled);
        LabelledAugmentedPaving fourth(grid,system);
        LabelledAugmentedPaving fifth(tree.euclidean_set(),system);
        LabelledAugmentedPaving sixth(Paving(new BinaryTreePaving(grid)),system);
        LabelledAugmentedPaving seventh(labelled_grid,system);
        LabelledAugmentedPaving eighth(tree,system);
        ARIADNE_TESTING_PROVE(fourth.is_empty() && sixth.is_empty() && seventh.is_empty());
        ARIADNE_TESTING_PROVE(subset(fifth,eighth));
        ARIADNE_TESTING_PROVE(intersect(first,eighth));
        second.adjoin(first);
        ARIADNE_TESTING_PROVE(subset(first,second));
        second.restrict(third);
        ARIADNE_TESTING_PROVE(second.is_empty());
        second.adjoin(first);
        second.remove(first);
        ARIADNE_TESTING_PROVE(second.is_empty());
        LabelledAugmentedPaving const& const_first=first;
        ARIADNE_TESTING_EXPECT_EQUAL(&first.euclidean_set(),static_cast<AugmentedPaving*>(&first));
        ARIADNE_TESTING_EXPECT_EQUAL(&const_first.euclidean_set(),
            static_cast<AugmentedPaving const*>(&first));
        ARIADNE_TESTING_EXPECT_EQUAL(first.grid().space(),state);
        ARIADNE_TESTING_EXPECT_EQUAL(first.auxiliary_data().argument_space(),state);
        ARIADNE_TESTING_EXPECT_EQUAL(first.auxiliary_data().result_space(),auxiliary);
        ARIADNE_TESTING_EXPECT_EQUAL(labelled.function().result_size(),1u);
        std::unique_ptr<LabelledAugmentedPaving> clone(first.clone());
        ARIADNE_TESTING_PROVE(subset(*clone,first));
        text<<first;
        ARIADNE_TESTING_PROVE(text.str().find("state_variables=")!=std::string::npos);

        LabelledAugmentedPaving mismatched(grid,other_state,mapping,auxiliary);
        ARIADNE_TESTING_EXPECT_EXCEPTION(second.adjoin(mismatched));
        ARIADNE_TESTING_EXPECT_EXCEPTION(second.restrict(mismatched));
        ARIADNE_TESTING_EXPECT_EXCEPTION(second.remove(mismatched));
        ARIADNE_TESTING_EXPECT_EXCEPTION(subset(first,mismatched));
        ARIADNE_TESTING_EXPECT_EXCEPTION(intersect(first,mismatched));
        LabelledGrid wrong_grid(grid,other_state);
        LabelledBinaryTreePaving wrong_tree(grid,other_state);
        ARIADNE_TESTING_EXPECT_EXCEPTION((LabelledAugmentedPaving(wrong_grid,labelled)));
        ARIADNE_TESTING_EXPECT_EXCEPTION((LabelledAugmentedPaving(wrong_tree,labelled)));
        ARIADNE_TESTING_EXPECT_EXCEPTION((LabelledAugmentedPaving(wrong_grid,system)));
        ARIADNE_TESTING_EXPECT_EXCEPTION((LabelledAugmentedPaving(wrong_tree,system)));
        ARIADNE_TESTING_EXPECT_EXCEPTION((LabelledPaving(Grid(1u),state)));
        ARIADNE_TESTING_EXPECT_EXCEPTION((LabelledAugmentedPaving(grid,RealSpace({x}),mapping,auxiliary)));
        ExactBoxSetType regular(ExactBoxType({{-1,1},{-1,1}}));
        auto approximation=inner_approximation(regular,labelled_grid,2u);
        ARIADNE_TESTING_EXPECT_EQUAL(approximation.space(),state);
        ARIADNE_TESTING_PROVE(!approximation.euclidean_set().is_empty());
    }

    Void test_generic_labelled_paving_shared_manager() {
        RealVariable x("x");
        RealSpace space({x});
        Grid grid(1u);
        auto manager=std::make_shared<RobddManager>();
        std::weak_ptr<RobddManager> weak=manager;
        LabelledPaving first(Paving(new RobddPaving(manager,grid)),space);
        LabelledPaving second(Paving(new RobddPaving(manager,grid)),space);
        manager.reset();
        GridCell root(grid,0u,BinaryWord{});
        first.euclidean_set().adjoin(root.split(false));
        second.euclidean_set().adjoin(root.split(true));
        ARIADNE_TESTING_PROVE(!weak.expired());
        ARIADNE_TESTING_EXPECT_EQUAL(first.space(),space);
        ARIADNE_TESTING_EXPECT_EQUAL(second.space(),space);
        Paving joined=join(
            static_cast<PavingInterface const&>(first.euclidean_set()),
            static_cast<PavingInterface const&>(second.euclidean_set()));
        ARIADNE_TESTING_PROVE(joined.superset(root));
        LabelledPaving copy(first);
        copy.euclidean_set().clear();
        ARIADNE_TESTING_PROVE(copy.euclidean_set().is_empty());
        ARIADNE_TESTING_PROVE(!first.euclidean_set().is_empty());
    }

    Void test_paving_and_drawing() {
        RealVariable x("x"),y("y"),z("z");
        RealSpace state({x,y}),auxiliary({z});
        EffectiveScalarMultivariateFunction coordinate=EffectiveScalarMultivariateFunction::coordinate(2u,0u);
        EffectiveVectorMultivariateFunction mapping({coordinate});
        LabelledMapping labelled(state,mapping,auxiliary);
        LabelledGrid labelled_grid(Grid(2u),state);
        LabelledAugmentedPaving paving(labelled_grid,labelled);
        ARIADNE_TESTING_PROVE(paving.is_empty());
        paving.adjoin_outer_approximation(ExactBoxType({{-1,1},{-1,1}}),2u);
        ARIADNE_TESTING_PROVE(paving.size()>0u);
        ARIADNE_TESTING_EXPECT_EQUAL(paving.state_space(),state);
        ARIADNE_TESTING_EXPECT_EQUAL(paving.auxiliary_space(),auxiliary);
        ARIADNE_TESTING_EXPECT_EQUAL(paving.state_auxiliary_paving().dimension(),3u);
        NullCanvas canvas;
        draw(canvas,Variables2d(x,y),paving);
        LabelledAugmentedPavingDrawable drawable(paving);
        drawable.draw(canvas,Variables2d(x,y));
        std::unique_ptr<LabelledDrawable2dInterface> clone(drawable.labelled_clone());
        clone->draw(canvas,Variables2d(x,y));
        Figure figure(ExactBoxType({{-2,2},{-2,2},{-2,2}}),Projection2d(3u,0u,1u));
        draw_to_figure(figure,paving);
        draw(figure,paving);
        ARIADNE_TESTING_EXPECT_EQUAL(&(figure<<paving),&figure);
        LabelledFigure labelled_figure(Axes2d(-2.0,x,2.0,-2.0,y,2.0));
        draw_to_figure(labelled_figure,paving);
        draw(labelled_figure,paving);
        ARIADNE_TESTING_EXPECT_EQUAL(&(labelled_figure<<paving),&labelled_figure);
        ARIADNE_TESTING_EXPECT_NO_THROW(labelled_figure._paint_all(canvas));
    }
};
int main(int argc,char** argv) {
    ARIADNE_TESTING_SUITE("test_augmented_paving");
    ARIADNE_TESTING_ADD_TEST(TestLabelledAugmentedPaving,test_generic_labelled_paving_shared_manager);
    ARIADNE_TESTING_ADD_TEST(TestLabelledAugmentedPaving,test_paving_and_drawing);
    ARIADNE_TESTING_ADD_TEST(TestLabelledAugmentedPaving,test_labelled_grid_and_augmented_operations);
    return ARIADNE_TESTING_RUN_TESTS_WITH_ARGS(argc,argv);
}
