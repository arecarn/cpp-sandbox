################################################################################
# Remove Dupes
################################################################################
add_executable(parity.test ${CMAKE_CURRENT_SOURCE_DIR}/parity.test.cpp)
target_link_libraries(parity.test gtest_main)
create_test(parity.test)
