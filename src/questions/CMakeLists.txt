project(questions)

# Is Unique
################################################################################
add_executable(is_unique.test
    ${CMAKE_CURRENT_SOURCE_DIR}/is_unique.test.cpp
)
target_link_libraries(is_unique.test
    gtest_main
)
create_test(is_unique.test)

# Reverse C String
################################################################################
add_executable(reverse_c_string.test
    ${CMAKE_CURRENT_SOURCE_DIR}/reverse_c_string.test.cpp
)
target_link_libraries(reverse_c_string.test
    gtest_main
)
create_test(reverse_c_string.test)
