################################################################################
# part 1
################################################################################
add_executable(aoc_2021_part_1 ${CMAKE_CURRENT_SOURCE_DIR}/part_1.cpp)
target_link_libraries(aoc_2021_part_1 gtest_main)

create_test(aoc_2021_part_1)
