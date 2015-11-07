set(NAME TestApp)
set(SRC src/TestApp.cpp)
add_executable(${NAME} MACOSX_BUNDLE ${SRC})
target_link_libraries(${NAME} unnamed ${EXTERNAL_LIBRARIES})
if(APPLE)
	set(LINKER_FLAGS "-framework Cocoa -framework OpenGL")
	set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_FLAGS}")
endif()

set_target_properties(${NAME} PROPERTIES
	OUTPUT_NAME "${NAME}"
	CLEAN_DIRECT_OUTPUT 1
)
if (APPLE)
    set_target_properties(${NAME} PROPERTIES
    	MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/tests/Info.plist.in)
endif ()
source_group(src FILES ${SRC})