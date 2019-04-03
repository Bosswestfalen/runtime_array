# bosswestfalen::runtime_array
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/bosswestfalen/runtime_array/master/LICENSE.MIT)
## Build

### Tests
CMake flag: `-DBUILD_TESTS=ON (default) or OFF`

Build unit-tests, using `Catch2`.

### Docs
CMake flag: `-DBUILD_DOCS=OFF (default) or ON`

Generate Doxygen documentation and store at `${CMAKE_BINARY_DIR}/docs`.

**Note:** make sure `doxygen` is installed.

### Analyse Code
CMake flag: `-DBUILD_CODEANALYSIS=OFF (default) or ON`

Analyze the code with `clang-tidy`.

**Note:** make sure `clang-tidy` is installed.

## Install
Use `cmake --build . --target install` to install `bosswestfalen/runtime_array.hpp` to `${CMAKE_INSTALL_PREFIX}/include/`

## Links
- [bosswestfalen::runtime_array](https://github.com/Bosswestfalen/runtime_array)
- [Catch2](https://https://github.com/catchorg/Catch2)
- [clang-tidy](https://clang.llvm.org/extra/clang-tidy)
- [CMake](https://cmake.org)
- [Doxygen](http://doxygen.nl)

