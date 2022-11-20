# Find FFTW++
find_path(FFTWPP_INCLUDE_DIR fftw++.h
          PATH_SUFFIXES fftwpp
          HINTS "${CMAKE_SOURCE_DIR}/vendor/fftwpp"
          REQUIRED
)

add_library(fftwpp INTERFACE IMPORTED)
target_include_directories(fftwpp INTERFACE "${FFTWPP_INCLUDE_DIR}/..")
target_sources(fftwpp INTERFACE "${FFTWPP_INCLUDE_DIR}/fftw++.cc")
target_link_libraries(fftwpp INTERFACE fftw3)

set_source_files_properties("fftw++.cc"
    TARGET_DIRECTORY fftwpp
    PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter"
)
