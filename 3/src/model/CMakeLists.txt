add_library(model STATIC
    student.cpp
    student.h
    juniorStudent.cpp
    juniorStudent.h
    seniorStudent.cpp
    seniorStudent.h
    studentInterface.h
    seniorInterface.h
)

target_include_directories(model PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

