find_package(Catch2 3 REQUIRED)

add_executable(tests test_point.cpp test_polygon.cpp)
target_compile_options(tests PRIVATE --coverage)
target_link_options(tests PRIVATE --coverage)
target_link_libraries(tests geometry_lib Catch2::Catch2WithMain)
target_include_directories(tests PRIVATE ../lib)