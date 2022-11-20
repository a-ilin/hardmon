cmake_minimum_required(VERSION 3.22)

project(hardmon LANGUAGES CXX)

# Add feature summary
include(FeatureSummary)

# Local cmake modules
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_SOURCE_DIR}/cmake
    ${CMAKE_SOURCE_DIR}/cmake_modules
)

include(consts)
include(options)
include(flags)
include(packages)

# testing
if(ENABLE_UNIT_TESTS)
    enable_testing()
    add_custom_target(check
        COMMAND ${CMAKE_CTEST_COMMAND} --verbose --output-on-failure
        USES_TERMINAL
    )
endif(ENABLE_UNIT_TESTS)

feature_summary(WHAT ALL)

# 3rd party libraries
add_subdirectory(vendor)

# source directory
add_subdirectory(src)
