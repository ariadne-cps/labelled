#ifndef ARIADNE_LABELLED_LABELLED_HPP
#define ARIADNE_LABELLED_LABELLED_HPP

#include "symbolic/space.hpp"

namespace Ariadne {

class Labelled {
  public:
    explicit Labelled(RealSpace const& space) : _space(space) { }

    RealSpace const& space() const { return _space; }
    Set<RealVariable> variables() const { return _space.variables(); }

  protected:
    RealSpace _space;
};

} // namespace Ariadne

#endif
