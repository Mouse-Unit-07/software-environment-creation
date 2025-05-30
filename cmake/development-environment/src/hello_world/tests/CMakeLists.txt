#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for hello_world test files                               #
#                                                                              #
#------------------------------------------------------------------------------#
set(LOCAL_TEST_SOURCES
    # ADD ALL TEST SOURCE FILES HERE
    ${CMAKE_CURRENT_SOURCE_DIR}/test_print_hello_world.cpp
    ${CMAKE_SOURCE_DIR}/src/hello_world/print_hello_world.c
)

set(ALL_TEST_SOURCES
    ${ALL_TEST_SOURCES}
    ${LOCAL_TEST_SOURCES}
    PARENT_SCOPE
)

add_executable(test_hello_world
    ${LOCAL_TEST_SOURCES}
    ${CMAKE_SOURCE_DIR}/tests/test_main.cpp
)

target_include_directories(test_hello_world PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)


target_link_libraries(test_hello_world PRIVATE
    hello_world_lib
    CppUTest
    CppUTestExt
)

add_test(NAME test_hello_world COMMAND test_hello_world)
