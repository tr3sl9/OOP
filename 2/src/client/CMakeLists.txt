add_library(client STATIC dialog.cpp dialog.h)

add_executable(main main.cpp)
add_executable(main_polygon main_polygon.cpp)

target_link_libraries(main client geometry_lib)
target_link_libraries(main_polygon client geometry_lib)
target_include_directories(main PRIVATE ../lib)
target_include_directories(main_polygon PRIVATE ../lib)
target_include_directories(client PRIVATE ../lib)