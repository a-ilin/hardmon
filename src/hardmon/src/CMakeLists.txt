set(TARGET ${PROJECT_NAME})

set(SOURCES
    CFftAnalysis.cpp
    CSensorReader.cpp
    CSignalHandler.cpp
)

add_library(${TARGET} "${SOURCES}")

target_include_directories(${TARGET}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)

target_link_libraries(${TARGET}
    PRIVATE
        ${Boost_LIBRARIES}
        pthread
        fftwpp
        HighFive
        yaml-cpp
)

add_subdirectory(plotfile)
add_subdirectory(sensor)
add_subdirectory(storage)
