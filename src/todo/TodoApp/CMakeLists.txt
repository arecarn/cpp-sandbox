################################################################################
# Library
################################################################################
add_library(TodoApp STATIC TodoApp.cpp)
target_link_libraries(TodoApp Todo)
target_include_directories(TodoApp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

################################################################################
# Test
################################################################################
add_executable(TodoApp.test TodoApp.test.cpp)
target_link_libraries(TodoApp.test TodoApp gtest_main)
create_test(TodoApp.test)
