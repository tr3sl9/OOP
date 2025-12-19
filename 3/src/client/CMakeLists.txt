add_executable(main_app main.cpp)

target_link_libraries(main_app model_lib)

target_include_directories(main_app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

target_compile_options(main_app PRIVATE --coverage)
target_link_options(main_app PRIVATE --coverage)

add_executable(benchmark benchmark.cpp)

target_link_libraries(benchmark model_lib pthread)

target_include_directories(benchmark PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

target_compile_options(benchmark PRIVATE --coverage)
target_link_options(benchmark PRIVATE --coverage)

