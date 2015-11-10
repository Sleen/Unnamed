#pragma once

#ifdef _WIN32
#   define UNNAMED_TARGET_WINDOWS   1
#elif defined(__APPLE__)
#   include "TargetConditionals.h"
#   if TARGET_OS_IPHONE
#       define UNNAMED_TARGET_IOS   1
#   else
#       define UNNAMED_TARGET_OSX   1
#   endif
#elif defined(__ANDROID__)
#   define UNNAMED_TARGET_ANDROID   1
#elif defined(__linux__)
#   define UNNAMED_TARGET_LINUX     1
#else
#   error "unknown platform"
#endif
