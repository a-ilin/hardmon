# This file contains all required packages for the project

find_package(PkgConfig REQUIRED)
find_package(yaml-cpp REQUIRED)

find_package(Boost REQUIRED COMPONENTS
                            filesystem
                            program_options
                            system
                            thread
)

# workaround for bug in CMake: https://gitlab.kitware.com/cmake/cmake/-/issues/18150
set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:${CMAKE_PREFIX_PATH}")

pkg_check_modules(fftw3 REQUIRED IMPORTED_TARGET fftw3)
include(Findfftwpp)

# Testing
if(ENABLE_UNIT_TESTS)
    find_package(GTest REQUIRED)
endif(ENABLE_UNIT_TESTS)
