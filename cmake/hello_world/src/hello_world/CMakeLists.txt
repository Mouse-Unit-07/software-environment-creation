#--------------------------------- FILE INFO ----------------------------------#
# Filename           : CMakeLists.txt                                          #
#                                                                              #
# CMakeLists.txt file for hello_world source files                             #
#                                                                              #
#------------------------------------------------------------------------------#
target_sources(hello_world_lib PRIVATE
    # ADD ALL .c SOURCE FILES HERE
    ${CMAKE_CURRENT_LIST_DIR}/print_hello_world.c
)

target_include_directories(hello_world_lib PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
