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
