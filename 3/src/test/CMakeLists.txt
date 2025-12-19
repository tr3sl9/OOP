include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.0
)

FetchContent_MakeAvailable(Catch2)

add_executable(unit_tests
    testStudent.cpp
    testGroup.cpp
    testUniversity.cpp
    testController.cpp
    testStudentTable.cpp
    testView.cpp
    testInputController.cpp
    testHashTable.cpp
)

target_link_libraries(unit_tests
    PRIVATE
    model_lib
    Catch2::Catch2WithMain
)

target_compile_options(unit_tests PRIVATE --coverage)
target_link_options(unit_tests PRIVATE --coverage)

target_include_directories(unit_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

include(CTest)
include(Catch)
Catch_discover_tests(unit_tests)

