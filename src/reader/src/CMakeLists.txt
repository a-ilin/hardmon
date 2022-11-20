set(TARGET ${PROJECT_NAME}-reader)

set(SOURCES
    reader.cpp
)

add_executable(${TARGET} "${SOURCES}")

target_link_libraries(${TARGET}
    PRIVATE
        ${PROJECT_NAME}
)

install(TARGETS ${TARGET})
