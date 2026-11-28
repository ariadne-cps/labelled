/***************************************************************************
 *            tests/test_value.cpp
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

/** @file tests/test_value.cpp
 *  @brief Verify the representation-independent labelled-value prototype.
 */

#include <string>
#include <utility>

#include "labelled/labelled.hpp"
#include "labelled/value.hpp"
#include "symbolic/space.hpp"

#include "ariadne-testing.hpp"

using namespace Ariadne;

namespace {
struct SizedValue {
    SizeType extent;

    SizeType dimension() const { return extent; }
};
} // namespace

class TestLabelledValue : public Ariadne::Testing::ContextFixture {
  public:
    using ContextFixture::ContextFixture;

    Void test_named_coordinates() {
        const RealVariable x("x");
        const RealVariable y("y");
        const RealSpace space({x, y});

        LabelledValue<SizedValue> value(SizedValue{2u}, space);
        ARIADNE_TESTING_EXPECT_EQUAL(value.value().dimension(), 2u);
        ARIADNE_TESTING_EXPECT_EQUAL(value.space(), space);
        ARIADNE_TESTING_EXPECT_EQUAL(value.variables(), space.variables());

        value.value().extent = 2u;
        ARIADNE_TESTING_EXPECT_EQUAL(value.value().dimension(), 2u);
    }

    Void test_dimension_validation() {
        const RealVariable x("x");
        ARIADNE_TESTING_EXPECT_EXCEPTION(
            (LabelledValue<SizedValue>(SizedValue{2u}, RealSpace({x}))));
    }

    Void test_arbitrary_metadata() {
        const RealVariable x("x");
        const RealVariable y("y");
        using Spaces = std::pair<RealSpace, RealSpace>;

        LabelledValue<std::string, Spaces> value(
            std::string("mapping"), Spaces{RealSpace({x}), RealSpace({y})});
        ARIADNE_TESTING_EXPECT_EQUAL(value.value(), std::string("mapping"));
        ARIADNE_TESTING_EXPECT_EQUAL(value.labels().first, RealSpace({x}));
        ARIADNE_TESTING_EXPECT_EQUAL(value.labels().second, RealSpace({y}));
    }

    Void test_labelled_printing() {
        const RealVariable x("x");
        const Labelled labelled(RealSpace({x}));
        ARIADNE_TESTING_NOTE(labelled);
    }
};

int main(int argc, char** argv) {
    ARIADNE_TESTING_SUITE("test_value");
    ARIADNE_TESTING_ADD_TEST(TestLabelledValue, test_named_coordinates);
    ARIADNE_TESTING_ADD_TEST(TestLabelledValue, test_dimension_validation);
    ARIADNE_TESTING_ADD_TEST(TestLabelledValue, test_arbitrary_metadata);
    ARIADNE_TESTING_ADD_TEST(TestLabelledValue, test_labelled_printing);
    return Ariadne::Testing::run_suite(ariadne_test_suite, argc, argv);
}
