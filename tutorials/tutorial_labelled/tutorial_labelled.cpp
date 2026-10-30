#include <iostream>

#include "ariadne-labelled.hpp"

using namespace Ariadne;

int main() {
    RealVariable x("x");
    RealVariable y("y");

    Axes2d axes(-2.0, x, 2.0, -1.5, y, 1.5);
    LabelledFigure figure(axes);

    LabelledSet<RealBox> region(
        RealSpace({x, y}),
        RealBox({
            {-1.25_dec, 0.75_dec},
            {-0.75_dec, 1.00_dec}
        })
    );

    figure.properties()
          .set_fill_opacity(0.40)
          .set_line_width(2.0);
    figure << region;
    figure.write("tutorial_labelled");

    std::cout << "space: " << region.space() << "\n";
    std::cout << "dimension: " << region.dimension() << "\n";
    return 0;
}
