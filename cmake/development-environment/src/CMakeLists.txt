#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for AT32UC3L0256 MCU build                               #
#                                                                              #
#------------------------------------------------------------------------------#
cmake_minimum_required(VERSION 4.0.2)
project(hello_world_lib LANGUAGES C)

# empty static library to start
add_library(hello_world_lib STATIC)

# ADD ALL SRC SUBDIRECTORIES HERE
add_subdirectory(hello_world)

target_include_directories(hello_world_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/hello_world
)
