################################################################################
# Remove Dupes
################################################################################
add_executable(
    remove_dupes.test
    ${CMAKE_CURRENT_SOURCE_DIR}/remove_dupes.test.cpp
)
target_link_libraries(remove_dupes.test gtest_main)
create_test(remove_dupes.test)

################################################################################
# Return Kth to Last
################################################################################
add_executable(
    return_kth_to_last.test
    ${CMAKE_CURRENT_SOURCE_DIR}/return_kth_to_last.test.cpp
)
target_link_libraries(return_kth_to_last.test gtest_main)
create_test(return_kth_to_last.test)

################################################################################
# Delete Middle Node
################################################################################
add_executable(
    delete_middle_node.test
    ${CMAKE_CURRENT_SOURCE_DIR}/delete_middle_node.test.cpp
)
target_link_libraries(delete_middle_node.test gtest_main)
create_test(delete_middle_node.test)
