add_subdirectory(include)
add_subdirectory(src)

if(ENABLE_UNIT_TESTS)
    add_subdirectory(test)
endif(ENABLE_UNIT_TESTS)
