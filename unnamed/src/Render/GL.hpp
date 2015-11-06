#pragma once

#ifdef _WIN32
#	define GLEW_STATIC
#	include "GL/glew.h"
#	include "GL/wglew.h"
#elif defined(__ANDROID__)
#	include <GLES/gl.h>
#	include <GLES2/gl2.h>
#	include <EGL/egl.h>
#elif defined(__APPLE__)
#	include <OpenGL/gl.h>
#endif
