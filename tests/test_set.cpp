/***************************************************************************
 *            tests/test_set.cpp
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

/** @file tests/test_set.cpp
 *  @brief Test labelled Euclidean set operations.
 */

#include "geometry/box.hpp"
#include "geometry/point.hpp"
#include "labelled/set.hpp"
#include "numeric/numeric.hpp"
#include "symbolic/space.hpp"

#include "ariadne-testing.hpp"
#include "expression-set/expression_set.hpp"

using namespace Ariadne;

class TestLabelledSet : public Ariadne::Testing::ContextFixture {
  private:
    RealVariable x{"x"}, y{"y"}, z{"z"};

  public:
    using ContextFixture::ContextFixture;

    Void test_set() {
        ARIADNE_TESTING_EXPECT_EXCEPTION(LabelledSet<RealBox>(
            RealSpace({
                x, y
        }),
            RealBox({{0.1_dec, 0.5_dec}, {-2.3_dec, 1}, {0, 3}})));

        LabelledSet<RealBox> set(RealSpace({
                                     x, y, z
        }),
                                 RealBox({{0.1_dec, 0.5_dec}, {-2.3_dec, 1}, {0, 3}}));
        ARIADNE_TESTING_EXPECT_EQUAL(set.dimension(), 3);
        ARIADNE_TESTING_EXPECT_EQUAL(set.space(), RealSpace({x, y, z}));
        ARIADNE_TESTING_EXPECT_EQUAL(set.variables(), Set<RealVariable>(RealSpace({x, y, z}).variables()));
        RealVariable u("u");
        ARIADNE_TESTING_EXPECT_NO_THROW(set.euclidean_set(RealSpace({y, z})));
        ARIADNE_TESTING_EXPECT_EXCEPTION(set.euclidean_set(RealSpace({y, u})));
    }

    Void test_point_adapter() {
        Map<RealVariable, Real> bindings;
        bindings.insert(x, 0.1_dec);
        bindings.insert(y, -1);
        VariablesPoint<Real> point(bindings);
        LabelledSet<RealPoint> labelled(point);
        ARIADNE_TESTING_EXPECT_EQUAL(labelled.dimension(), 2);
    }

    Void test_box_adapter() {
        RealVariablesBox box(RealSpace({
                                 x, y
        }),
                             RealBox({{0.1_dec, 0.5_dec}, {-2.3_dec, 1}}));
        LabelledSet<RealBox> labelled(box);
        ARIADNE_TESTING_EXPECT_EQUAL(labelled.dimension(), 2);
        const auto& labelled_x = labelled.euclidean_set()[labelled.space().index(x)];
        ARIADNE_TESTING_PROVE(labelled_x.lower_bound().pointer() == box[x].lower_bound().pointer());
        ARIADNE_TESTING_PROVE(labelled_x.upper_bound().pointer() == box[x].upper_bound().pointer());
    }
};

int main(int argc, char** argv) {
    ARIADNE_TESTING_SUITE("test_set");
    ARIADNE_TESTING_ADD_TEST(TestLabelledSet, test_set);
    ARIADNE_TESTING_ADD_TEST(TestLabelledSet, test_point_adapter);
    ARIADNE_TESTING_ADD_TEST(TestLabelledSet, test_box_adapter);
    return ARIADNE_TESTING_RUN_TESTS_WITH_ARGS(argc, argv);
}
