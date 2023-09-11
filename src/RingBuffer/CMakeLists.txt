################################################################################
# Library
################################################################################
add_library(RingBuffer INTERFACE)
target_include_directories(RingBuffer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

################################################################################
# Test
################################################################################
add_executable(RingBufferTest ${CMAKE_CURRENT_SOURCE_DIR}/RingBufferTest.cpp)
target_link_libraries(RingBufferTest gtest_main RingBuffer)
create_test(RingBufferTest)
