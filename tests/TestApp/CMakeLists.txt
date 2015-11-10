set(NAME TestApp)
set(SRC src/TestApp.cpp)
source_group(src FILES ${SRC})

add_executable(${NAME} MACOSX_BUNDLE ${SRC})
target_link_libraries(${NAME} unnamed ${EXTERNAL_LIBS})

set_target_properties(${NAME} PROPERTIES
	OUTPUT_NAME "${NAME}"
	CLEAN_DIRECT_OUTPUT 1
)

if (IOS)
	set(LINKER_FLAGS "-framework Foundation -framework UIKit -framework GLKit -framework OpenGLES")
	set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_FLAGS}")
elseif (APPLE)
	set(LINKER_FLAGS "-framework Cocoa -framework OpenGL")
	set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_FLAGS}")
endif ()

if (NOT DEFINED MACOSX_BUNDLE_GUI_IDENTIFIER)
	set(MACOSX_BUNDLE_GUI_IDENTIFIER me.sleen.unnamed.test_app)
endif ()

if (IOS)
	set_target_properties(${NAME} PROPERTIES
    	MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/tests/iOS/Info.plist.in)
elseif (APPLE)
    set_target_properties(${NAME} PROPERTIES
    	MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/tests/OSX/Info.plist.in)
endif ()
