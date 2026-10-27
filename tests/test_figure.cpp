#include "macro/testing.hpp"
#include "labelling/figure.hpp"
#include "drawing/box_draw.hpp"
#include "rendering/null_rendering.hpp"
#include "logging/logging.hpp"

#include <array>
#include <cstdio>
#include <fstream>

using namespace Ariadne;

// Record the axes passed to the renderer, including when a bounds update
// supplies only one of the two coordinates.
class BoundsCanvas : public NullCanvas {
  public:
    Void initialise(StringType, StringType, double xl, double xu,
                    double yl, double yu) override {
        initialized=true;
        x_lower=xl; x_upper=xu;
        y_lower=yl; y_upper=yu;
    }

    Bool initialized=false;
    double x_lower=0.0, x_upper=0.0, y_lower=0.0, y_upper=0.0;
};

class TestLabelledFigure {
  public:
    void test() {
        ARIADNE_TEST_CALL(test_projection())
        ARIADNE_TEST_CALL(test_construction())
        ARIADNE_TEST_CALL(test_drawing())
        ARIADNE_TEST_CALL(test_invalid_axes())
        ARIADNE_TEST_CALL(test_style_modifiers())
        ARIADNE_TEST_CALL(test_png_export())
    }

    void test_projection() {
        RealVariable x("x"), y("y"), z("z");
        RealSpace space({x,y});
        Projection2d regular=projection(space,Variables2d(x,y));
        ARIADNE_TEST_EQUALS(regular.argument_size(),2u)
        ARIADNE_TEST_EQUALS(regular.x_coordinate(),0u)
        ARIADNE_TEST_EQUALS(regular.y_coordinate(),1u)

        Projection2d time_projection=projection(RealSpace({y}),Variables2d(TimeVariable(),y));
        ARIADNE_TEST_EQUALS(time_projection.x_coordinate(),1u)
        ARIADNE_TEST_EQUALS(time_projection.y_coordinate(),0u)

        // When time is already a coordinate, the ordinary index is used.
        Projection2d contained_time=projection(RealSpace({TimeVariable(),y}),Variables2d(TimeVariable(),y));
        ARIADNE_TEST_EQUALS(contained_time.argument_size(),2u)
        ARIADNE_TEST_EQUALS(contained_time.x_coordinate(),0u)
        ARIADNE_TEST_EQUALS(contained_time.y_coordinate(),1u)

        ARIADNE_TEST_FAIL(projection(space,Variables2d(z,y)))
        ARIADNE_TEST_FAIL(projection(space,Variables2d(x,z)))
    }

    void test_construction() {
        RealVariable x("x"), y("y"), z("z");
        ApproximateBoxType bounds({
            {FloatDPApproximation(0.0,dp),FloatDPApproximation(1.0,dp)},
            {FloatDPApproximation(-1.0,dp),FloatDPApproximation(1.0,dp)}
        });
        // A one-dimensional box violates the public two-axis precondition.
        // Exercise the rejection, rather than fabricating an impossible state.
        ApproximateBoxType one_dimensional_bounds({
            {FloatDPApproximation(0.0,dp),FloatDPApproximation(1.0,dp)}
        });
        ARIADNE_TEST_FAIL(LabelledFigure(Variables2d(x,y),
            VariablesBox<ApproximateIntervalType>(
                RealSpace({x}),one_dimensional_bounds)))

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

        // Incomplete bounds cannot replace the last valid two-axis viewport.
        figure.set_bounds({{y,ApproximateDoubleInterval(-2.0,2.0)}});
        BoundsCanvas incomplete;
        figure._paint_all(incomplete);
        ARIADNE_TEST_ASSERT(incomplete.initialized)
        ARIADNE_TEST_EQUALS(incomplete.x_lower,0.0)
        ARIADNE_TEST_EQUALS(incomplete.x_upper,1.0)
        ARIADNE_TEST_EQUALS(incomplete.y_lower,-1.0)
        ARIADNE_TEST_EQUALS(incomplete.y_upper,1.0)

        // Once both axes are present, the rendered viewport must change.
        figure.set_bounds({{x,ApproximateDoubleInterval(-3.0,3.0)},
                           {y,ApproximateDoubleInterval(-4.0,4.0)}});
        BoundsCanvas complete;
        figure._paint_all(complete);
        ARIADNE_TEST_EQUALS(complete.x_lower,-3.0)
        ARIADNE_TEST_EQUALS(complete.x_upper,3.0)
        ARIADNE_TEST_EQUALS(complete.y_lower,-4.0)
        ARIADNE_TEST_EQUALS(complete.y_upper,4.0)
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

    void test_style_modifiers() {
        RealVariable x("x"), y("y");
        LabelledFigure figure(Axes2d(-1.0,x,1.0,-1.0,y,1.0));

        // Exercise the stream-style API and verify every observable setting.
        figure << line_style(false)
               << line_width(2.5)
               << line_colour(0.25,0.5,0.75)
               << fill_style(false)
               << fill_colour(0.6,0.4,0.2)
               << fill_opacity(0.35)
               << Ariadne::set_animated(true);

        LabelledFigure const& const_figure=figure;
        RenderingProperties const& properties=const_figure.properties();
        ARIADNE_TEST_EQUALS(properties.line_style,false)
        ARIADNE_TEST_EQUALS(properties.line_width,2.5)
        ARIADNE_TEST_EQUALS(properties.line_colour.red,0.25)
        ARIADNE_TEST_EQUALS(properties.line_colour.green,0.5)
        ARIADNE_TEST_EQUALS(properties.line_colour.blue,0.75)
        ARIADNE_TEST_EQUALS(properties.fill_style,false)
        ARIADNE_TEST_EQUALS(properties.fill_colour.red,0.6)
        ARIADNE_TEST_EQUALS(properties.fill_colour.green,0.4)
        ARIADNE_TEST_EQUALS(properties.fill_colour.blue,0.2)
        ARIADNE_TEST_EQUALS(properties.fill_colour.opacity,0.35)
        ARIADNE_TEST_EQUALS(properties.is_animated,true)
    }

    static unsigned int png_dimension(std::array<unsigned char,24> const& header, SizeType start) {
        return (static_cast<unsigned int>(header[start])<<24u)
             | (static_cast<unsigned int>(header[start+1])<<16u)
             | (static_cast<unsigned int>(header[start+2])<<8u)
             | static_cast<unsigned int>(header[start+3]);
    }

    void verify_png(const char* filename, unsigned int width, unsigned int height) {
        std::ifstream image(filename,std::ios::binary);
        ARIADNE_TEST_ASSERT(image.is_open())
        std::array<unsigned char,24> header{};
        image.read(reinterpret_cast<char*>(header.data()),static_cast<std::streamsize>(header.size()));
        ARIADNE_TEST_EQUALS(image.gcount(),static_cast<std::streamsize>(header.size()))
        ARIADNE_TEST_EQUALS(static_cast<unsigned int>(header[0]),137u)
        ARIADNE_TEST_EQUALS(static_cast<unsigned int>(header[1]),80u)
        ARIADNE_TEST_EQUALS(static_cast<unsigned int>(header[2]),78u)
        ARIADNE_TEST_EQUALS(static_cast<unsigned int>(header[3]),71u)
        // The size passed to Figure::write is the plot area. Rendering
        // adds 160+10 pixels for horizontal margins (axis labels) and
        // 10+40 pixels for vertical margins before writing the PNG.
        constexpr unsigned int horizontal_margins=160u+10u;
        constexpr unsigned int vertical_margins=10u+40u;
        ARIADNE_TEST_EQUALS(png_dimension(header,16u),width+horizontal_margins)
        ARIADNE_TEST_EQUALS(png_dimension(header,20u),height+vertical_margins)
        image.close();
        ARIADNE_TEST_EQUALS(std::remove(filename),0)
    }

    void test_png_export() {
        RealVariable x("x"), y("y");
        LabelledFigure figure(Axes2d(-1.0,x,1.0,-1.0,y,1.0));

        // Validate both overloads against the actual PNG file format.
        figure.write("test_labelling_default.png");
        verify_png("test_labelling_default.png",800u,800u);

        figure.write("test_labelling_sized.png",64u,48u);
        verify_png("test_labelling_sized.png",64u,48u);
    }
};

int main() {
    TestLabelledFigure().test();
    return ARIADNE_TEST_FAILURES;
}
