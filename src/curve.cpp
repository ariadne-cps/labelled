#include "labelled/curve.hpp"
#include "labelled/figure.hpp"

namespace Ariadne {

LabelledInterpolatedCurve::LabelledInterpolatedCurve(const PointType& pt)
    : InterpolatedCurve(CurveInterface::PointType(pt)), Labelled(pt.space()) { }

LabelledInterpolatedCurve* LabelledInterpolatedCurve::labelled_clone() const {
    return new LabelledInterpolatedCurve(*this);
}

Void LabelledInterpolatedCurve::draw(CanvasInterface& c, const Variables2d& v) const {
    Projection2d proj=projection(this->space(),v);
    Ariadne::draw(c,proj,static_cast<InterpolatedCurve const&>(*this));
}

} // namespace Ariadne
