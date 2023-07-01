################################################################################
# Library
################################################################################
add_library(TodoList INTERFACE)
target_include_directories(TodoList INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(TodoList INTERFACE Todo)
