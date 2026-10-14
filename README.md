# Ariadne Labelling

[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Unix Status](https://github.com/ariadne-cps/labelling/actions/workflows/unix.yml/badge.svg)](https://github.com/ariadne-cps/labelling/actions/workflows/unix.yml)
[![Windows Status](https://github.com/ariadne-cps/labelling/actions/workflows/win.yml/badge.svg)](https://github.com/ariadne-cps/labelling/actions/workflows/win.yml)
[![Coverage Status](https://github.com/ariadne-cps/labelling/actions/workflows/coverage.yml/badge.svg)](https://github.com/ariadne-cps/labelling/actions/workflows/coverage.yml)
[![codecov](https://codecov.io/gh/ariadne-cps/labelling/branch/main/graph/badge.svg)](https://codecov.io/gh/ariadne-cps/labelling)

Ariadne Labelling is the standalone C++20 labelled-geometry and labelled-drawing layer used by Ariadne. It provides labelled points, curves, sets, figures and variable-aware drawing facilities on top of Ariadne Kernel.

## Layout

Public headers live under `include/labelling`, implementations under `src`, C++ tests under `tests`, Python bindings and tests under `python`, and standalone examples under `tutorials`.

The umbrella header is `include/ariadne-labelling.hpp`.

## Dependencies

Labelling currently depends directly on:

- [ariadne-cps/kernel](https://github.com/ariadne-cps/kernel), included as a Git submodule.
- [ariadne-cps/configuration](https://github.com/ariadne-cps/configuration), used for shared build configuration.

Kernel supplies the symbolic, geometry and drawing facilities used by Labelling. This dependency is intentionally temporary while the Symbolic module is being separated.

## Build

```bash
git clone --recurse-submodules https://github.com/ariadne-cps/labelling.git
cd labelling
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel --target everything
ctest --test-dir build --output-on-failure
```

## Python bindings

When a compatible Python development environment is available, the standalone build produces `pyariadne` from the Kernel bindings plus the Labelling bindings.

## License

Ariadne Labelling is released under the GNU General Public License v3.0.
