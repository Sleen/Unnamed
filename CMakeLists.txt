project(Unnamed)

set(UNNAMED_INC 
	${CMAKE_SOURCE_DIR}/unnamed/src
	${CMAKE_SOURCE_DIR}/external/glew/include
)

set(EXTERNAL_LIBRARIES "")
if (WIN32)
	set(EXTERNAL_LIBRARIES ${EXTERNAL_LIBRARIES} glew opengl32)
endif ()

add_subdirectory(external)
add_subdirectory(unnamed)
add_subdirectory(tests)
