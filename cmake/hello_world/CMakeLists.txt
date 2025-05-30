#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file to build a simple Hello World project                    #
# Targets AVR32 MCU and Windows for unit testing                               #
#                                                                              #
#------------------------------------------------------------------------------#
cmake_minimum_required(VERSION 4.0.2)
project(hello_world_project LANGUAGES C CXX)

# Build option is selected w/ presets file
option(TARGET_MCU "Build for AVR32 MCU" OFF)
option(TARGET_WINDOWS "Build for Windows (unit tests)" OFF)

# Always build the shared static library
add_subdirectory(src)

# Hardware build
if(TARGET_MCU)
    add_subdirectory(avr32)
endif()

# Windows build w/ unit tests
if(TARGET_WINDOWS)
    enable_testing()
    add_subdirectory(tests)
endif()
