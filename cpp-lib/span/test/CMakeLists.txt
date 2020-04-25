add_executable(span_test
    ${CMAKE_CURRENT_SOURCE_DIR}/span_test.cpp
)

target_link_libraries(span_test
    span
    array
    gtest_main
)

create_test(span_test)
