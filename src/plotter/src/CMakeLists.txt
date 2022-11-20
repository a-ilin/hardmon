set(TARGET ${PROJECT_NAME}-plotter)

set(SOURCES
    plotter.cpp
)

add_executable(${TARGET} "${SOURCES}")

target_link_libraries(${TARGET}
    PRIVATE
        ${PROJECT_NAME}
)

install(TARGETS ${TARGET})
