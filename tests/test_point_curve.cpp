/***************************************************************************
 *            test_point_curve.cpp
 *
 *  Copyright  2005-21  Luca Geretti
 *
 ****************************************************************************/

/*
 *  This file is part of Ariadne.
 *
 *  Ariadne is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Ariadne is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Ariadne.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "numeric/module.hpp"
#include "geometry/point.hpp"
#include "labelled/point.hpp"
#include "labelled/curve.hpp"
#include "set/curve.hpp"
#include "symbolic/space.hpp"
#include "symbolic/assignment.hpp"
#include "drawing/point_draw.hpp"
#include "drawing/geometry_draw.hpp"
#include "rendering/null_rendering.hpp"

#include "ariadne-testing.hpp"

using namespace Ariadne;

class TestCurveCanvas : public NullCanvas {
  public:
    Void move_to(double, double) override { moved=true; }
    Void line_to(double, double) override { lined=true; }

    Bool moved=false;
    Bool lined=false;
};

class TestPointCanvas : public NullCanvas {
  public:
    Void dot(double, double) override { dotted=true; }
    Void stroke() override { stroked=true; }

    Bool dotted=false;
    Bool stroked=false;
};

template<class X> class TestPoint : public Ariadne::Testing::ContextFixture {
    typedef LabelledPoint<X> PointType;
  public:
    using ContextFixture::ContextFixture;

    void test_creation() {
        RealVariable x("x"), y("y");
        LabelledPoint<Real> rpt({x=3,y=2.1_dec});
        PointType pt(rpt,dp);

        ARIADNE_TESTING_EXPECT_EQUAL(class_name<LabelledPoint<Real>>(),String("LabelledPoint<Real>"));
        ARIADNE_TESTING_EXPECT_EQUAL(class_name<LabelledPoint<FloatDPApproximation>>(),String("LabelledPoint<FloatDPApproximation>"));

        ARIADNE_TESTING_EXPECT_EQUAL(pt.dimension(),2);
        ARIADNE_TESTING_EXPECT_EQUAL(pt.space(),RealSpace({x,y}));
        ARIADNE_TESTING_EXPECT_EQUAL(pt.variables(),Set<RealVariable>(RealSpace({x,y}).variables()));
        ARIADNE_TESTING_NOTE(pt.bounding_box());

        std::unique_ptr<PointType> clone(pt.labelled_clone());
        ARIADNE_TESTING_EXPECT_EQUAL(clone->dimension(),pt.dimension());
        ARIADNE_TESTING_EXPECT_EQUAL(clone->space(),pt.space());
        ARIADNE_TESTING_EXPECT_EQUAL(clone->variables(),pt.variables());

        TestPointCanvas canvas;
        pt.draw(canvas,Variables2d(x,y));
        ARIADNE_TESTING_PROVE(canvas.dotted);
        ARIADNE_TESTING_PROVE(canvas.stroked);
    }

    void test_projection() {
        RealVariable x("x"), y("y"), z("z");
        LabelledPoint<Real> rpt({x=3,y=2.1_dec,z=1/5_q});
        PointType pt(rpt,dp);
        ARIADNE_TESTING_NOTE(pt);
        ARIADNE_TESTING_EXPECT_EQUAL(pt.dimension(),3);

        auto pt_pr = project(pt,Variables2d(z,x));
        ARIADNE_TESTING_NOTE(pt_pr);
        ARIADNE_TESTING_EXPECT_EQUAL(pt_pr.dimension(),2);
        ARIADNE_TESTING_EXPECT_SAME(pt.at(0),pt_pr.at(1));
        ARIADNE_TESTING_EXPECT_SAME(pt.at(2),pt_pr.at(0));
    }
};

class TestCurve : public Ariadne::Testing::ContextFixture {
    typedef LabelledInterpolatedCurve CurveType;
    typedef CurveType::PointType PointType;
  public:
    using ContextFixture::ContextFixture;

    void test_creation() {
        RealVariable x("x"), y("y");
        LabelledPoint<Real> rpt({x=3,y=2.1_dec});
        PointType pt(rpt,dp);
        CurveType curve(pt);
        ARIADNE_TESTING_EXPECT_EQUAL(curve.dimension(),2);
        ARIADNE_TESTING_EXPECT_EQUAL(curve.space(),pt.space());
        ARIADNE_TESTING_EXPECT_EQUAL(curve.variables(),pt.variables());
        ARIADNE_TESTING_EXPECT_EQUAL(curve.size(),1);
        curve.insert(FloatDP(1.0_x,dp),pt);
        ARIADNE_TESTING_EXPECT_EQUAL(curve.size(),2);

        std::unique_ptr<CurveType> clone(curve.labelled_clone());
        ARIADNE_TESTING_EXPECT_EQUAL(clone->dimension(),curve.dimension());
        ARIADNE_TESTING_EXPECT_EQUAL(clone->space(),curve.space());
        ARIADNE_TESTING_EXPECT_EQUAL(clone->size(),curve.size());

        TestCurveCanvas canvas;
        curve.draw(canvas,Variables2d(x,y));
        ARIADNE_TESTING_PROVE(canvas.moved);
        ARIADNE_TESTING_PROVE(canvas.lined);
    }
};


int main(int argc, char** argv) {
    ARIADNE_TESTING_SUITE("test_point_curve");
    ARIADNE_TESTING_ADD_TEST(TestPoint<FloatDPApproximation>, test_creation);
    ARIADNE_TESTING_ADD_TEST(TestPoint<FloatDPApproximation>, test_projection);
    ARIADNE_TESTING_ADD_TEST(TestCurve, test_creation);
    return ARIADNE_TESTING_RUN_TESTS_WITH_ARGS(argc, argv);
}
