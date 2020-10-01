################################################################################
# Rotate Matrix
################################################################################
add_executable(
    rotate_matrix.test
    ${CMAKE_CURRENT_SOURCE_DIR}/rotate_matrix.test.cpp
)
target_link_libraries(rotate_matrix.test gtest_main)
target_set_default_compiler_warnings(rotate_matrix.test)
create_test(rotate_matrix.test)

################################################################################
# Zero Matrix
################################################################################
add_executable(
    zero_matrix.test
    ${CMAKE_CURRENT_SOURCE_DIR}/zero_matrix.test.cpp
)
target_link_libraries(zero_matrix.test gtest_main)
target_set_default_compiler_warnings(zero_matrix.test)
create_test(zero_matrix.test)
