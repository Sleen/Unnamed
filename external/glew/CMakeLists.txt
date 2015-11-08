add_definitions("-DGLEW_STATIC")
add_library(glew glew.c)
set_property(GLOBAL APPEND PROPERTY EXTERNAL_LIBS glew)
