cmake_minimum_required(VERSION 3.20)
project(SearchInFile VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src/lib)

set(SOURCES_CLIENT src/client/main.cpp)
set(SOURCES_LIB src/lib/stringlib.cpp)

add_executable(main ${SOURCES_CLIENT} ${SOURCES_LIB})

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

target_link_libraries(main readline)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-fanalyzer)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compile_options(-fanalyzer)
endif()

if(UNIX AND NOT APPLE)
    find_program(VALGRIND valgrind)
    if(VALGRIND)
        add_custom_target(memcheck
            COMMAND valgrind --leak-check=full --error-exitcode=1 ./main
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
    endif()
endif()