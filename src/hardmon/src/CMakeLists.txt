set(TARGET ${PROJECT_NAME})

set(SOURCES
    hardmon.cpp
)

add_library(${TARGET} "${SOURCES}")

target_include_directories(${TARGET}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)

target_link_libraries(${TARGET}
    PRIVATE
        yaml-cpp
)
