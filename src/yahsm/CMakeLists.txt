# Library
################################################################################
add_library(yahsm INTERFACE)
target_include_directories(yahsm INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Test
################################################################################
add_executable(yahsm.test ${CMAKE_CURRENT_SOURCE_DIR}/yahsm.test.cpp)
target_link_libraries(yahsm.test gtest_main yahsm)
create_test(yahsm.test)
