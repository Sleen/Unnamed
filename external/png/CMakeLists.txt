aux_source_directory(. SRC)
target_link_libraries(z)
add_library(png ${SRC})
set_property(GLOBAL APPEND PROPERTY EXTERNAL_LIBS png)
