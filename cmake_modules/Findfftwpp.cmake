# Find FFTW++
find_path(FFTWPP_DIR fftw++.h
          PATH_SUFFIXES fftwpp
          HINTS "${CMAKE_SOURCE_DIR}/vendor/fftwpp"
          REQUIRED
)

get_filename_component(FFTWPP_INCLUDE_DIR "${FFTWPP_DIR}/.."
    ABSOLUTE
    BASE_DIR /
    CACHE
)

add_library(fftwpp)
target_include_directories(fftwpp SYSTEM PUBLIC "${FFTWPP_INCLUDE_DIR}")
target_sources(fftwpp PRIVATE "${FFTWPP_DIR}/fftw++.cc")
target_link_libraries(fftwpp PUBLIC fftw3 fftw3_omp)
target_link_options(fftwpp PUBLIC -fopenmp)
target_compile_options(fftwpp
    PUBLIC
        -fopenmp
    PRIVATE
        -Wno-unused-parameter
)
