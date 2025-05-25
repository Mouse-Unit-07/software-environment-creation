#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file to build a simple Hello World project                    #
# Targets AVR32 MCU and Windows for unit testing                               #
#                                                                              #
#------------------------------------------------------------------------------#
cmake_minimum_required(VERSION 4.0.2)

project(hello_world_project LANGUAGES C CXX)

option(TARGET_WINDOWS "Enable building of tests" OFF)

if(TARGET_MCU)
    add_subdirectory(src)
endif()

if(TARGET_WINDOWS)
    enable_testing()
    add_subdirectory(tests)
endif()