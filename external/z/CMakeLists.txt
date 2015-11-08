aux_source_directory(. SRC)
add_library(z ${SRC})
set_property(GLOBAL APPEND PROPERTY EXTERNAL_LIBS z)
