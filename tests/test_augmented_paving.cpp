#include "labelled/labelled_augmented_paving.hpp"
#include "labelled/labelled_augmented_paving_draw.hpp"
#include "rendering/null_rendering.hpp"
#include "ariadne-testing.hpp"

using namespace Ariadne;

class TestLabelledAugmentedPaving : public Ariadne::Testing::ContextFixture {
  public:
    using ContextFixture::ContextFixture;
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
    }
};
int main(int argc,char** argv) {
    ARIADNE_TESTING_SUITE("test_augmented_paving");
    ARIADNE_TESTING_ADD_TEST(TestLabelledAugmentedPaving,test_paving_and_drawing);
    return ARIADNE_TESTING_RUN_TESTS_WITH_ARGS(argc,argv);
}
