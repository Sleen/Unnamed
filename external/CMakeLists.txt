project(external)

#include_directories(${external_SOURCE_DIR}/include)

set(LIBRARY_OUTPUT_PATH ${external_SOURCE_DIR}/libs/${CMAKE_SYSTEM_NAME})

if (WIN32)
	add_subdirectory(glew)
	add_subdirectory(z)
	set_property(GLOBAL APPEND PROPERTY EXTERNAL_LIBS opengl32)
else ()
	set_property(GLOBAL APPEND PROPERTY EXTERNAL_LIBS z)
endif ()

add_subdirectory(minizip)
add_subdirectory(png)
add_subdirectory(freetype2)
add_subdirectory(lua)
