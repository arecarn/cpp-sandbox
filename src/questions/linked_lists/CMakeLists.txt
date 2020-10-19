################################################################################
# Linked List Node
################################################################################
add_library(list_node.il INTERFACE)
target_include_directories(list_node.il INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_set_default_compiler_warnings(list_node.il)
add_library(list_node.sl STATIC ${CMAKE_CURRENT_SOURCE_DIR}/list_node.cpp)
target_link_libraries(list_node.sl list_node.il)

################################################################################
# Remove Dupes
################################################################################
add_executable(
    remove_dupes.test
    ${CMAKE_CURRENT_SOURCE_DIR}/remove_dupes.test.cpp
)
target_link_libraries(remove_dupes.test gtest_main)
target_set_default_compiler_warnings(remove_dupes.test)
create_test(remove_dupes.test)

################################################################################
# Return Kth to Last
################################################################################
add_executable(
    return_kth_to_last.test
    ${CMAKE_CURRENT_SOURCE_DIR}/return_kth_to_last.test.cpp
)
target_link_libraries(return_kth_to_last.test gtest_main)
target_set_default_compiler_warnings(return_kth_to_last.test)
create_test(return_kth_to_last.test)

################################################################################
# Delete Middle Node
################################################################################
add_executable(
    delete_middle_node.test
    ${CMAKE_CURRENT_SOURCE_DIR}/delete_middle_node.test.cpp
)
target_link_libraries(delete_middle_node.test gtest_main)
target_set_default_compiler_warnings(delete_middle_node.test)
create_test(delete_middle_node.test)

################################################################################
# Merge Two Sorted Lists
################################################################################
add_executable(
    merged_two_sorted_lists.test
    ${CMAKE_CURRENT_SOURCE_DIR}/merged_two_sorted_lists.test.cpp
)
target_link_libraries(merged_two_sorted_lists.test gtest_main)
target_set_default_compiler_warnings(merged_two_sorted_lists.test)
create_test(merged_two_sorted_lists.test)
