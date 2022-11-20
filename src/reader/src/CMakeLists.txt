set(TARGET ${PROJECT_NAME}-reader)

set(SOURCES
    reader.cpp
)

add_executable(${TARGET} "${SOURCES}")

target_link_libraries(${TARGET}
    PRIVATE
        ${PROJECT_NAME}
)

target_compile_definitions(${TARGET}
    PRIVATE
        READER_CONFIG_FILE=\"${READER_CONFIG_FILE}\"
)

install(TARGETS ${TARGET})
