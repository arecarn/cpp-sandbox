################################################################################
# Library
################################################################################
add_library(todo_app STATIC todo_app.cpp)
target_link_libraries(todo_app todo)
target_include_directories(todo_app PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

################################################################################
# Test
################################################################################
add_executable(todo_app.test todo_app.test.cpp)
target_link_libraries(todo_app.test todo_app gtest_main)
create_test(todo_app.test)

