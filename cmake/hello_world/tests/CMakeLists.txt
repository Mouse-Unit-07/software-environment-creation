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

set(ALL_SOURCE_FILES_EXCEPT_MAIN
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
        ${CMAKE_SOURCE_DIR}/src/main.c
        ${ALL_SOURCE_FILES_EXCEPT_MAIN}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running Cppcheck on manually listed sources"
    VERBATIM
)

set(FORMATTED_SOURCES "")
foreach(src ${ALL_SOURCE_FILES_EXCEPT_MAIN})
    # Make path relative to project root
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

add_executable(test_print_hello_world
    ${ALL_SOURCE_FILES_EXCEPT_MAIN}
)

target_include_directories(test_print_hello_world PRIVATE
    ${CMAKE_SOURCE_DIR}/src/hello_world
)

target_link_libraries(test_print_hello_world PRIVATE
    CppUTest
    CppUTestExt
)

add_test(NAME PrintHelloTest COMMAND test_print_hello_world)
