# This file contains all required packages for the project

find_package(yaml-cpp REQUIRED)

# Testing
if(ENABLE_UNIT_TESTS)
    find_package(GTest REQUIRED)
endif(ENABLE_UNIT_TESTS)
