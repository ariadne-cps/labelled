# Ariadne Labelling

[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Unix Status](https://github.com/ariadne-cps/labelling/actions/workflows/unix.yml/badge.svg)](https://github.com/ariadne-cps/labelling/actions/workflows/unix.yml)
[![Windows Status](https://github.com/ariadne-cps/labelling/actions/workflows/win.yml/badge.svg)](https://github.com/ariadne-cps/labelling/actions/workflows/win.yml)
[![Sanitizers Status](https://github.com/ariadne-cps/labelling/actions/workflows/sanitizers.yml/badge.svg)](https://github.com/ariadne-cps/labelling/actions/workflows/sanitizers.yml)
[![Coverage Status](https://github.com/ariadne-cps/labelling/actions/workflows/coverage.yml/badge.svg)](https://github.com/ariadne-cps/labelling/actions/workflows/coverage.yml)
[![codecov](https://codecov.io/gh/ariadne-cps/labelling/branch/main/graph/badge.svg)](https://codecov.io/gh/ariadne-cps/labelling)

Ariadne Labelling is the standalone C++20 labelled-geometry and labelled-drawing layer used by Ariadne. It provides labelled points, curves, sets, boxes, figures and variable-aware drawing facilities on top of Ariadne Symbolic.

## Layout

Public headers live under `include/labelling`, implementations under `src`, C++ tests under `tests`, Python bindings and tests under `python`, and standalone examples under `tutorials`.

The umbrella header is `include/ariadne-labelling.hpp`.

## Dependencies

Labelling depends directly on:

- [ariadne-cps/symbolic](https://github.com/ariadne-cps/symbolic), included as a Git submodule.
- [ariadne-cps/drawing](https://github.com/ariadne-cps/drawing), included as a Git submodule, for geometric drawing and rendering.
- [ariadne-cps/configuration](https://github.com/ariadne-cps/configuration), used for shared build configuration.

Symbolic supplies the symbolic layer and transitively Kernel; Drawing supplies the drawing adapters and transitively Rendering. Shared transitive dependencies must use consistent commits.

## Build

```bash
git clone --recurse-submodules https://github.com/ariadne-cps/labelling.git
cd labelling
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel --target everything
ctest --test-dir build --output-on-failure
```

## Python bindings

When a compatible Python development environment is available, the standalone build produces and installs `pyariadne`, combining the Symbolic, Drawing, Rendering and Labelling bindings with their transitive dependencies.

## Contribution guidelines

If you would like to contribute to Ariadne Labelling, please contact the developer:

- Luca Geretti <luca.geretti@univr.it>

## License

Ariadne Labelling is released under the GNU General Public License v3.0.
