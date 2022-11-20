set(TARGET ${PROJECT_NAME}_test)

set(SOURCES
    main.cpp
    CSensorReaderTest.cpp
)

add_executable(${TARGET} ${SOURCES})

target_link_libraries(
    ${TARGET}
    PRIVATE
        ${PROJECT_NAME}
        gmock
        gtest
)

add_test(NAME ${TARGET} COMMAND ${TARGET})
