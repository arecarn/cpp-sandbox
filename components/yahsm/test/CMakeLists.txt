add_executable(yahsm_test
    ${CMAKE_CURRENT_SOURCE_DIR}/yahsm_test.cpp
)

target_link_libraries(
    yahsm_test
    gtest_main
    yahsm
)

create_test(yahsm_test)
