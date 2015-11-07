set(NAME UnitTest)
set(SRC 
	src/UnitTest.hpp
	src/Test.cpp
	src/TestColor.hpp
	src/TestIO.hpp
	src/TestMath.hpp
	src/TestString.hpp
	)
add_executable(${NAME} ${SRC})
target_link_libraries(${NAME} unnamed)
if(APPLE)
	set(LINKER_FLAGS "-framework Cocoa -framework OpenGL")
	set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_FLAGS}")
endif()

set_target_properties(${NAME} PROPERTIES
	OUTPUT_NAME "${NAME}"
	CLEAN_DIRECT_OUTPUT 1
)

source_group(src FILES ${SRC})
