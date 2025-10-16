add_library(geometry_lib STATIC point.cpp point.h polygon.h)
target_compile_options(geometry_lib PUBLIC --coverage)
target_link_options(geometry_lib PUBLIC --coverage)