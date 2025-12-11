add_library(view STATIC
    tableView.cpp
    tableView.h
)

target_include_directories(view PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(view PUBLIC
    model
    repository
)

target_compile_options(view PRIVATE --coverage)
target_link_options(view PRIVATE --coverage)

