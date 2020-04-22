add_executable(test_ringbuffer
    ${CMAKE_CURRENT_SOURCE_DIR}/test_ringbuffer.cpp
)

target_link_libraries(test_ringbuffer
    gtest_main
    ringbuffer
)

create_test(test_ringbuffer)
