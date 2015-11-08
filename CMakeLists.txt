project(Unnamed)

include_directories(
	${CMAKE_SOURCE_DIR}/unnamed/src
	${CMAKE_SOURCE_DIR}/external/include
)

add_subdirectory(external)

get_property(EXTERNAL_LIBS GLOBAL PROPERTY EXTERNAL_LIBS)

add_subdirectory(unnamed)
add_subdirectory(tests)
