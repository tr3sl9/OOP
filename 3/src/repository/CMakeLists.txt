add_library(repository STATIC
    group.cpp
    group.h
    studentTable.cpp
    studentTable.h
    university.cpp
    university.h
    groupInterface.h
)

target_include_directories(repository PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(repository PUBLIC
    model
    template
)

