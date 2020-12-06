################################################################################
# Binary Tree Node
################################################################################
add_library(binary_tree_node INTERFACE)
target_include_directories(binary_tree_node INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_set_default_compiler_warnings(binary_tree_node)
add_library(binary_tree_node.check STATIC ${CMAKE_CURRENT_SOURCE_DIR}/binary_tree_node.check.cpp)
target_link_libraries(binary_tree_node.check binary_tree_node)
