project(questions)

add_executable(is_unique.test
    ${CMAKE_CURRENT_SOURCE_DIR}/is_unique.test.cpp
)
target_link_libraries(is_unique.test
    gtest_main
)
create_test(is_unique.test)
