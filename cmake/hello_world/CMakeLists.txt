#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# Test file to build a simple Hello World project                              #
#                                                                              #
#------------------------------------------------------------------------------#

cmake_minimum_required(VERSION 4.0.2)

set(CMAKE_VERBOSE_MAKEFILE ON)

project(hello_world
    DESCRIPTION "Hello World test project"
    LANGUAGES C)

# Source files
add_executable(hello_world 
    main.c
)

# Build artifact extension
set_target_properties(hello_world PROPERTIES SUFFIX ".elf")

# Include directories
target_include_directories(hello_world PRIVATE
    "C:/Program Files (x86)/Atmel/Studio/7.0/Packs/atmel/UC3L_DFP/1.0.59/include/AT32UC3L0256"
)

# Custom post build steps (e.g., HEX, EEP, SREC)
add_custom_command(TARGET hello_world POST_BUILD
    COMMAND "$CACHE{AVR32_OBJCOPY}" -O ihex -R .eeprom -R .fuse -R .lock -R .signature $<TARGET_FILE:hello_world> hello_world.hex
    COMMAND "$CACHE{AVR32_OBJCOPY}" -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex $<TARGET_FILE:hello_world> hello_world.eep
    COMMAND "$CACHE{AVR32_OBJCOPY}" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures $<TARGET_FILE:hello_world> hello_world.srec
    COMMAND "$CACHE{AVR32_OBJDUMP}" -h -S $<TARGET_FILE:hello_world> > hello_world.lss
    COMMAND ${AVR32_SIZE} --format=berkeley $<TARGET_FILE:hello_world>
    COMMENT "Generating HEX, EEP, SREC, LSS"
)