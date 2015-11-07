include_directories(${UNNAMED_INC})

set(UNNAMED_LIBRARIES unnamed)

add_definitions(-std=c++11)

add_subdirectory(TestApp)
add_subdirectory(UnitTest)
