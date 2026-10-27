#include "macro/testing.hpp"
#include "labelling/figure.hpp"
#include "drawing/box_draw.hpp"
#include "rendering/null_rendering.hpp"
#include "logging/logging.hpp"

using namespace Ariadne;

class TestLabelledFigure {
public:
    void test() {
        ARIADNE_TEST_CALL(test_projection())
        ARIADNE_TEST_CALL(test_construction())
        ARIADNE_TEST_CALL(test_drawing())
        ARIADNE_TEST_CALL(test_invalid_axes())
    }

    void test_projection() {
        RealVariable x("x"), y("y"), z("z");
        RealSpace space({x,y});
        Projection2d regular = projection(space,Variables2d(x,y));
        ARIADNE_TEST_EQUALS(regular.argument_size(),2u)
        ARIADNE_TEST_EQUALS(regular.x_coordinate(),0u)
        ARIADNE_TEST_EQUALS(regular.y_coordinate(),1u)
        Projection2d time_projection = projection(RealSpace({y}),Variables2d(TimeVariable(),y));
        ARIADNE_TEST_EQUALS(time_projection.x_coordinate(),1u)
        ARIADNE_TEST_EQUALS(time_projection.y_coordinate(),0u)
        ARIADNE_TEST_FAIL(projection(space,Variables2d(z,y)))
        ARIADNE_TEST_FAIL(projection(space,Variables2d(x,z)))
    }

    void test_construction() {
        RealVariable x("x"), y("y"), z("z");
        ApproximateBoxType bounds({
            {FloatDPApproximation(0.0,dp),FloatDPApproximation(1.0,dp)},
            {FloatDPApproximation(-1.0,dp),FloatDPApproximation(1.0,dp)}
        });
        ARIADNE_TEST_FAIL(LabelledFigure(Variables2d(x,z),
            VariablesBox<ApproximateIntervalType>(RealSpace({x,y}),bounds)))
        LabelledFigure figure(Variables2d(x,y),
            VariablesBox<ApproximateIntervalType>(RealSpace({x,y}),bounds));
        ARIADNE_TEST_EXECUTE(figure.set_axes(Axes2d({0<=x<=1,-1<=y<=2})))
        ARIADNE_TEST_EXECUTE(figure.set_bounds(x,ApproximateDoubleInterval(1.0,2.0)))
        ARIADNE_TEST_EXECUTE(figure.set_bounds({
            {x,ApproximateDoubleInterval(1.0,2.0)},
            {y,ApproximateDoubleInterval(0.0,1.0)}}))
        ARIADNE_TEST_EXECUTE(figure.set_bounding_box(
            VariablesBox<ApproximateIntervalType>(RealSpace({x,y}),bounds)))
        ARIADNE_TEST_PRINT(figure.properties())
    }

    void test_invalid_axes() {
        RealVariable empty(""), x("x"), y("y");
        NullCanvas canvas;
        LabelledFigure empty_x(Axes2d(-1.0,empty,1.0,-1.0,y,1.0));
        ARIADNE_TEST_FAIL(empty_x._paint_all(canvas))
        LabelledFigure empty_y(Axes2d(-1.0,x,1.0,-1.0,empty,1.0));
        ARIADNE_TEST_FAIL(empty_y._paint_all(canvas))
    }

    void test_drawing() {
        RealVariable x("x"), y("y");
        LabelledFigure figure(Axes2d(-2.0,x,2.0,-1.5,y,1.5));
        LabelledSet<RealBox> region(
            RealSpace({x,y}),
            RealBox({{-1.25_dec,0.75_dec},{-0.75_dec,1.00_dec}}));
        figure.properties().set_line_style(false).set_fill_style(false).set_dot_radius(2.0);
        ARIADNE_TEST_EQUALS(figure.properties().line_style,false)
        figure.draw(LabelledDrawableWrapper<RealBox>(region));
        draw(figure,LabelledDrawableWrapper<RealBox>(region));
        figure << region;
        figure.set_animated(true);
        NullCanvas canvas;
        ARIADNE_TEST_EXECUTE(figure._paint_all(canvas))
        ARIADNE_TEST_EXECUTE(figure.clear())
    }
};

int main() {
    TestLabelledFigure().test();
    return ARIADNE_TEST_FAILURES;
}
