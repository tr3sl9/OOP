add_subdirectory(../template template)
add_subdirectory(../model model)
add_subdirectory(../repository repository)
add_subdirectory(../view view)
add_subdirectory(../controller controller)

add_library(model_lib INTERFACE)

target_link_libraries(model_lib INTERFACE
    model
    repository
    view
    controller
    template
)

