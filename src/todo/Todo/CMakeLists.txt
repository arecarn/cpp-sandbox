################################################################################
# Library
################################################################################
add_library(Todo INTERFACE)
target_include_directories(Todo INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

################################################################################
# Test
################################################################################
add_executable(Todo.test Todo.test.cpp)
target_link_libraries(Todo.test Todo gtest_main)
create_test(Todo.test)
