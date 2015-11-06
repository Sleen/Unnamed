include_directories(
    ${CMAKE_SOURCE_DIR}/unnamed/src
)

set(UNNAMED_LIBRARIES unnamed)

add_definitions(-std=c++11)

add_subdirectory(TestApp)
add_subdirectory(UnitTest)
