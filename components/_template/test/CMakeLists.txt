add_executable(template
    ${CMAKE_CURRENT_SOURCE_DIR}/template.cpp
)

target_link_libraries(
    template
    gtest_main
    template_static
)

create_test(template)
