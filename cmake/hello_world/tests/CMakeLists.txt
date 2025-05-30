#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for Windows build                                        #
#                                                                              #
#------------------------------------------------------------------------------#
cmake_minimum_required(VERSION 4.0.2)
project(hello_world_tests LANGUAGES C CXX)

include(FetchContent)
FetchContent_Declare(
    CppUTest
    GIT_REPOSITORY https://github.com/cpputest/cpputest.git
    GIT_TAG master
)
FetchContent_MakeAvailable(CppUTest)

set(TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_print_hello_world.cpp
    ${CMAKE_SOURCE_DIR}/src/hello_world/print_hello_world.c
)

add_executable(test_print_hello_world ${TEST_SOURCES})

target_include_directories(test_print_hello_world PRIVATE
    ${CMAKE_SOURCE_DIR}/src/hello_world
)

target_link_libraries(test_print_hello_world PRIVATE
    hello_world_lib
    CppUTest
    CppUTestExt
)

add_test(NAME PrintHelloTest COMMAND test_print_hello_world)

# === Static Analysis: Cppcheck ===
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
        ${CMAKE_SOURCE_DIR}/src/main.c
        ${TEST_SOURCES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running Cppcheck on source and test files"
    VERBATIM
)

# === Formatting: clang-format ===
set(FORMATTED_SOURCES "")
foreach(src ${TEST_SOURCES})
    file(RELATIVE_PATH rel_path "${CMAKE_SOURCE_DIR}" "${src}")
    set(formatted_file "${CMAKE_BINARY_DIR}/clang-format-output/${rel_path}")
    list(APPEND FORMATTED_SOURCES "${formatted_file}")

    get_filename_component(formatted_file_dir "${formatted_file}" DIRECTORY)

    add_custom_command(
        OUTPUT "${formatted_file}"
        COMMAND ${CMAKE_COMMAND} -E make_directory "${formatted_file_dir}"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${src}" "${formatted_file}"
        COMMAND clang-format -i -style=file "${formatted_file}"
        DEPENDS "${src}"
        COMMENT "Formatting ${rel_path} -> ${formatted_file}"
    )
endforeach()

add_custom_target(format_sources DEPENDS ${FORMATTED_SOURCES})
