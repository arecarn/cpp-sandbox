################################################################################
# Library
################################################################################
add_library(span INTERFACE)
target_include_directories(span INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

################################################################################
# Test
################################################################################
add_executable(span.test ${CMAKE_CURRENT_SOURCE_DIR}/span.test.cpp)
target_link_libraries(span.test span array gtest_main)
create_test(span.test)
