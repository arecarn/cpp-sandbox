################################################################################
# Library
################################################################################
add_library(array INTERFACE)
target_include_directories(array INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_set_default_compiler_warnings(array)

################################################################################
# Test
################################################################################
add_executable(array.test ${CMAKE_CURRENT_SOURCE_DIR}/array.test.cpp)
target_link_libraries(array.test array gtest_main)
create_test(array.test)
