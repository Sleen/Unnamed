#pragma once

#include "Target.hpp"

#if UNNAMED_TARGET_WINDOWS
#	define GLEW_STATIC
#	include "GL/glew.h"
#	include "GL/wglew.h"

#elif UNNAMED_TARGET_OSX
#   include <OpenGL/gl.h>

#elif UNNAMED_TARGET_ANDROID
#	include <GLES/gl.h>
#	include <GLES2/gl2.h>
#	include <EGL/egl.h>

#elif UNNAMED_TARGET_IOS
#	include <OpenGLES/ES2/gl.h>
#	include <OpenGLES/ES2/glext.h>
#   define GL_DEPTH24_STENCIL8 GL_DEPTH24_STENCIL8_OES

#endif
