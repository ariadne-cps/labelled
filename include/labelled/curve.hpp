#ifndef ARIADNE_LABELLED_CURVE_HPP
#define ARIADNE_LABELLED_CURVE_HPP

#include "set/curve.hpp"
#include "labelled/point.hpp"

namespace Ariadne {

class LabelledInterpolatedCurve
    : public LabelledDrawable2dInterface,
      public InterpolatedCurve,
      public Labelled
{
  public:
    typedef LabelledPoint<FloatDPApproximation> PointType;

    explicit LabelledInterpolatedCurve(const PointType& pt);

    LabelledInterpolatedCurve* labelled_clone() const override;

    Void draw(CanvasInterface&, const Variables2d&) const override;
};

} // namespace Ariadne

#endif
