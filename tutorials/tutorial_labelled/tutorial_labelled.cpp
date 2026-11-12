/***************************************************************************
 *            tutorials/tutorial_labelled/tutorial_labelled.cpp
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

/** @file tutorials/tutorial_labelled/tutorial_labelled.cpp
 *  @brief Demonstrate labelled geometry rendering.
 */

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
