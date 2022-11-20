set(TARGET ${PROJECT_NAME}_test)

set(SOURCES
    main.cpp
)

add_executable(${TARGET} ${SOURCES})

target_link_libraries(
    ${TARGET}
    PRIVATE
        gtest
        pthread
        ${PROJECT_NAME}
)

add_test(NAME ${TARGET} COMMAND ${TARGET})
