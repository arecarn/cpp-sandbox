################################################################################
# Rotate Matrix
################################################################################
add_executable(
    rotate_matrix.test
    ${CMAKE_CURRENT_SOURCE_DIR}/rotate_matrix.test.cpp
)
target_link_libraries(rotate_matrix.test gtest_main)

create_test(rotate_matrix.test)

################################################################################
# Zero Matrix
################################################################################
add_executable(
    zero_matrix.test
    ${CMAKE_CURRENT_SOURCE_DIR}/zero_matrix.test.cpp
)
target_link_libraries(zero_matrix.test gtest_main)

################################################################################
# Zero Matrix
################################################################################
add_executable(
    dutch_national_flag.test
    ${CMAKE_CURRENT_SOURCE_DIR}/dutch_national_flag.test.cpp
)
target_link_libraries(dutch_national_flag.test gtest_main)

create_test(dutch_national_flag.test)
