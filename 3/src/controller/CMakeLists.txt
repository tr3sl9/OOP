add_library(controller STATIC
    highLevelController.cpp
    highLevelController.h
    inputController.cpp
    inputController.h
)

target_include_directories(controller PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(controller PUBLIC
    model
    repository
    view
)

target_compile_options(controller PRIVATE --coverage)
target_link_options(controller PRIVATE --coverage)

