# Ariadne Labelled

[![macOS Status](https://github.com/ariadne-cps/labelled/actions/workflows/macos.yml/badge.svg)](https://github.com/ariadne-cps/labelled/actions/workflows/macos.yml)
[![Ubuntu Status](https://github.com/ariadne-cps/labelled/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/ariadne-cps/labelled/actions/workflows/ubuntu.yml)
[![Windows Status](https://github.com/ariadne-cps/labelled/actions/workflows/win.yml/badge.svg)](https://github.com/ariadne-cps/labelled/actions/workflows/win.yml)
[![Sanitizers Status](https://github.com/ariadne-cps/labelled/actions/workflows/sanitizers.yml/badge.svg)](https://github.com/ariadne-cps/labelled/actions/workflows/sanitizers.yml)
[![Coverage Status](https://github.com/ariadne-cps/labelled/actions/workflows/coverage.yml/badge.svg)](https://github.com/ariadne-cps/labelled/actions/workflows/coverage.yml)
[![codecov](https://codecov.io/gh/ariadne-cps/labelled/branch/main/graph/badge.svg)](https://codecov.io/gh/ariadne-cps/labelled)

Ariadne Labelled is the standalone C++20 labelled-geometry and labelled-drawing layer used by Ariadne. It provides labelled points, curves, sets, boxes, figures and variable-aware drawing facilities on top of Ariadne Expression Set and Drawing.

## Layout

Public headers live under `include/labelled`, implementations under `src`, C++ tests under `tests`, Python bindings and tests under `python`, and standalone examples under `tutorials`.

The umbrella header is `include/ariadne-labelled.hpp`.

## Dependencies

Labelled depends directly on:

- [ariadne-cps/expression-set](https://github.com/ariadne-cps/expression-set), Git submodule `ss/exp`, for labelled bounds, symbolic sets and the underlying Symbolic and Set modules.
- [ariadne-cps/drawing](https://github.com/ariadne-cps/drawing), Git submodule `ss/dra`, for geometric drawing and rendering.
- [ariadne-cps/configuration](https://github.com/ariadne-cps/configuration), Git submodule `ss/cfg`, for shared CMake infrastructure.

Expression Set supplies Symbolic and Set transitively; Drawing supplies Paving, Rendering and Set transitively. The build checks that shared Configuration, Set and Function dependencies use consistent commits. Kernel is not a dependency.

## Build

```bash
git clone --recurse-submodules https://github.com/ariadne-cps/labelled.git
cd labelled
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel --target everything
ctest --test-dir build --output-on-failure
```

## Python bindings

When a compatible Python development environment is available, the standalone build produces and installs `pyariadne`, combining the Expression Set, Drawing and Labelled bindings with their transitive dependencies, including Symbolic, Set, Paving and Rendering.

## Contribution guidelines

If you would like to contribute to Ariadne Labelled, please contact the developer:

- Luca Geretti <luca.geretti@univr.it>

## License

Ariadne Labelled is released under the GNU General Public License v3.0.
