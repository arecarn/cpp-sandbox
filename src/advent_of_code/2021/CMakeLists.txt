################################################################################
# part 1
################################################################################
add_executable(aoc_2021_part_1 ${CMAKE_CURRENT_SOURCE_DIR}/part_1.cpp)
target_link_libraries(aoc_2021_part_1 gtest_main)
target_set_default_compiler_warnings(aoc_2021_part_1)
create_test(aoc_2021_part_1)
