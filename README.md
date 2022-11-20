# Description
This project is set of command-line tools to read and analyze hardware sensors.


# Command line

### hardmon-reader

TBD


### hardmon-plotter

TBD


# Build dependencies

All necessary build dependencies mentioned below may be installed on Ubuntu with the following command:
```sh
sudo apt install build-essentials cmake g++ libyaml-cpp-dev libboost-all-dev libhdf5-dev libfftw3-dev libgtest-dev libgmock-dev
```

### Compiler
GCC is being as a compiler during development. Another compiler should be compatible as well.


### CMake
CMake is an open-source, cross-platform family of tools designed to build, test and package software.
<https://cmake.org/>


### yaml-cpp
yaml-cpp is a YAML parser and emitter in C++ matching the YAML 1.2 spec.

<https://github.com/jbeder/yaml-cpp>


### HighFive
HighFive - HDF5 header-only C++ Library.
Added as a Git submodule.

<https://github.com/BlueBrain/HighFive>


### hdf5
Hierarchical Data Format 5.

<https://www.hdfgroup.org/solutions/hdf5>


### FFTW
FFTW is a C subroutine library for computing the discrete Fourier transform (DFT).

<https://www.fftw.org/>


### FFTW++
FFTW++: Fast Fourier Transform C++ Header/MPI Transpose for FFTW3.
Added as a Git submodule.

<https://fftwpp.sourceforge.net/>


### boost >= 1.41
Boost provides free peer-reviewed portable C++ source libraries.

<https://www.boost.org/>


### GTest & GMock
Google Test is a C++ test framework.

<https://github.com/google/googletest>


# Installation

### Configuration
Ensure that submodules are loaded:
```sh
git submodule update --init --recursive
```

To configure the project use CMake. Example command:
```sh
cmake <source_directory>
```

### Build
Command to build:
```sh
cmake --build . --target all
```


### Testing
Testing is implemented using GTest.

Tests can be launched using `ctest` program from CMake package.

Alternatively `check` target can be built:
```sh
cmake --build . --target check
```
