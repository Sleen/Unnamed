set(UNNAMED_SRC
	src/Application.cpp
	src/Application.hpp
	src/Configs.h
	src/Main.cpp
	src/OSXWindow.hpp
	src/OSXWindow.mm
	src/Unnamed.hpp
	src/Window.cpp
	src/Window.hpp
	src/String.cpp
	src/String.hpp
	src/Base/Log.cpp
	src/Base/StringHelper.cpp
	src/Base/System.cpp
	src/Math/Math.cpp
	src/Math/Matrix.cpp
	src/Render/Bitmap.cpp
	src/Render/BitmapLoader.cpp
	src/Render/Brush.cpp
	src/Render/Graphics.cpp
	src/Render/Pen.cpp
	src/Render/Program.cpp
	src/Render/Texture.cpp
	src/Render/Transform.cpp
	src/IO/FileStream.cpp
	src/IO/FileSystem.cpp
	src/IO/MemoryStream.cpp
	src/IO/Stream.cpp
)

include_directories(src)

add_definitions(-std=c++11)

add_library(unnamed STATIC ${UNNAMED_SRC})
set_target_properties(unnamed PROPERTIES
	OUTPUT_NAME "unnamed"
	CLEAN_DIRECT_OUTPUT 1
)
source_group(src FILES ${UNNAMED_SRC})