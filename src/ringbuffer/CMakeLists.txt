################################################################################
# Library
################################################################################
add_library(ringbuffer INTERFACE)
target_include_directories(ringbuffer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


################################################################################
# Test
################################################################################
add_executable(ringbuffer.test ${CMAKE_CURRENT_SOURCE_DIR}/ringbuffer.test.cpp)
target_link_libraries(ringbuffer.test gtest_main ringbuffer)
create_test(ringbuffer.test)
