add_executable(tagged_union_test
    ${CMAKE_CURRENT_SOURCE_DIR}/tagged_union_test.cpp
)

target_include_directories(tagged_union_test
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(tagged_union_test
    gtest_main
)

create_test(tagged_union_test)
