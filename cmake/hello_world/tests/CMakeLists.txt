#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for Windows build                                        #
#                                                                              #
#------------------------------------------------------------------------------#
cmake_minimum_required(VERSION 4.0.2)
project(tests LANGUAGES C CXX)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  CppUTest
  GIT_REPOSITORY https://github.com/cpputest/cpputest.git
  GIT_TAG master
)
FetchContent_MakeAvailable(CppUTest)

get_target_property(CPPUTEST_INCLUDE_DIR CppUTest INTERFACE_INCLUDE_DIRECTORIES)

set(CPP_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/main.c
    ${CMAKE_SOURCE_DIR}/src/hello_world/print_hello_world.c
    ${CMAKE_SOURCE_DIR}/tests/test_print_hello_world.cpp
    ${CMAKE_SOURCE_DIR}/tests/test_main.cpp
)

add_custom_target(cppcheck
    COMMAND cppcheck
        --enable=all
        --inconclusive
        --quiet
        --std=c99
        --force
        --inline-suppr
        --suppress=missingIncludeSystem
        -I ${CMAKE_SOURCE_DIR}/src/hello_world
        #-I ${CPPUTEST_INCLUDE_DIR}
        ${CPP_SOURCE_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running Cppcheck on manually listed sources"
    VERBATIM
)

add_executable(test_print_hello_world
    ${CMAKE_SOURCE_DIR}/src/hello_world/print_hello_world.c
    test_print_hello_world.cpp
    test_main.cpp
)

target_include_directories(test_print_hello_world PRIVATE
    ${CMAKE_SOURCE_DIR}/src/hello_world
)

target_link_libraries(test_print_hello_world PRIVATE
    CppUTest
    CppUTestExt
)

add_test(NAME PrintHelloTest COMMAND test_print_hello_world)
