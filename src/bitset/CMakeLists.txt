################################################################################
# Library
################################################################################
add_library(bitset INTERFACE)
target_include_directories(bitset INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_set_default_compiler_warnings(bitset)

################################################################################
# Test
################################################################################
add_executable(bitset.test ${CMAKE_CURRENT_SOURCE_DIR}/bitset.test.cpp)
target_link_libraries(bitset.test bitset gtest_main)
create_test(bitset.test)
