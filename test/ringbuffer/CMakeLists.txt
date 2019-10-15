add_executable(test_ringbuffer
    ${CMAKE_CURRENT_SOURCE_DIR}/test_ringbuffer.cpp
)

target_include_directories(test_ringbuffer
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(test_ringbuffer
    gtest_main
)

create_test(test_ringbuffer)
