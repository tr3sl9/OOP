cmake_minimum_required(VERSION 3.20)

project(oopprog3 VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_ANALYZER "Enable static analyzer" OFF)
if(ENABLE_ANALYZER)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        add_compile_options(-fanalyzer)
        message(STATUS "Static analyzer enabled (may produce false positives)")
    endif()
endif()

add_subdirectory(src/lib)
add_subdirectory(src/test)
add_subdirectory(src/client)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/docs)
    
    add_custom_target(docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Генерация документации с помощью Doxygen"
        VERBATIM
    )
    
    add_custom_target(docs_clean
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${DOXYGEN_OUT}
        COMMENT "Очистка сгенерированной документации"
    )
    
    message(STATUS "Doxygen найден: ${DOXYGEN_EXECUTABLE}")
    message(STATUS "Документация будет сгенерирована в: ${DOXYGEN_OUT}")
    message(STATUS "Для генерации документации выполните: make docs")
else()
    message(WARNING "Doxygen не найден. Документация не будет сгенерирована.")
    message(WARNING "Установите Doxygen для генерации документации.")
endif()

