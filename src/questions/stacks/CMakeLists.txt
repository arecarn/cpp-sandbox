################################################################################
# Stack With Max
################################################################################
add_executable(stack_with_max.test ${CMAKE_CURRENT_SOURCE_DIR}/stack_with_max.test.cpp)
target_link_libraries(stack_with_max.test gtest_main)
target_set_default_compiler_warnings(stack_with_max.test)
create_test(stack_with_max.test)
