#include "ariadne-testing.hpp"
#include "numeric/numeric.hpp"
#include "geometry/point.hpp"
#include "geometry/box.hpp"
#include "expression-set/expression_set.hpp"
#include "symbolic/space.hpp"
#include "labelled/set.hpp"

using namespace Ariadne;

class TestLabelledSet : public Ariadne::Testing::ContextFixture {
  private:
    RealVariable x{"x"}, y{"y"}, z{"z"};

  public:
    using ContextFixture::ContextFixture;

    Void test_set() const {
        ARIADNE_TESTING_EXPECT_EXCEPTION(LabelledSet<RealBox>(
            RealSpace({x,y}),
            RealBox({{0.1_dec,0.5_dec},{-2.3_dec,1},{0,3}})
        ));

        LabelledSet<RealBox> set(RealSpace({x,y,z}),RealBox({{0.1_dec,0.5_dec},{-2.3_dec,1},{0,3}}));
        ARIADNE_TESTING_EXPECT_EQUAL(set.dimension(),3);
        ARIADNE_TESTING_EXPECT_EQUAL(set.space(),RealSpace({x,y,z}));
        ARIADNE_TESTING_EXPECT_EQUAL(set.variables(),Set<RealVariable>(RealSpace({x,y,z}).variables()));
        RealVariable u("u");
        ARIADNE_TESTING_EXPECT_NO_THROW(set.euclidean_set(RealSpace({y,z})));
        ARIADNE_TESTING_EXPECT_EXCEPTION(set.euclidean_set(RealSpace({y,u})));
    }

    Void test_point_adapter() const {
        Map<RealVariable,Real> bindings;
        bindings.insert(x,0.1_dec);
        bindings.insert(y,-1);
        VariablesPoint<Real> point(bindings);
        LabelledSet<RealPoint> labelled(point);
        ARIADNE_TESTING_EXPECT_EQUAL(labelled.dimension(),2);
    }

    Void test_box_adapter() const {
        RealVariablesBox box(RealSpace({x,y}),RealBox({{0.1_dec,0.5_dec},{-2.3_dec,1}}));
        LabelledSet<RealBox> labelled(box);
        ARIADNE_TESTING_EXPECT_EQUAL(labelled.dimension(),2);
        auto const& labelled_x=labelled.euclidean_set()[labelled.space().index(x)];
        ARIADNE_TESTING_PROVE(labelled_x.lower_bound().pointer()==box[x].lower_bound().pointer());
        ARIADNE_TESTING_PROVE(labelled_x.upper_bound().pointer()==box[x].upper_bound().pointer());
    }
};

int main(int argc, char** argv) {
    ARIADNE_TESTING_SUITE("test_set");
    ARIADNE_TESTING_ADD_TEST(TestLabelledSet, test_set);
    ARIADNE_TESTING_ADD_TEST(TestLabelledSet, test_point_adapter);
    ARIADNE_TESTING_ADD_TEST(TestLabelledSet, test_box_adapter);
    return ARIADNE_TESTING_RUN_TESTS_WITH_ARGS(argc, argv);
}
