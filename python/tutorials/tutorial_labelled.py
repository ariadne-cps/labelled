#!/usr/bin/python3

from pyariadne import *

x = RealVariable("x")
y = RealVariable("y")

axes = Axes2d(-2.0, x, 2.0, -1.5, y, 1.5)
figure = LabelledFigure(axes)

box = LabelledRealBox(
    RealSpace([x, y]),
    RealBox([
        RealInterval(Real(Decimal("-1.25")), Real(Decimal("0.75"))),
        RealInterval(Real(Decimal("-0.75")), Real(Decimal("1.0"))),
    ]),
)

figure.draw(box)
figure.write("tutorial_labelled")
print("dimension:", box.dimension())
