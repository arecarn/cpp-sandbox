################################################################################
# Library
################################################################################
add_library(ObjectPool INTERFACE)
target_include_directories(ObjectPool INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

################################################################################
# Test
################################################################################
add_executable(ObjectPoolTest ${CMAKE_CURRENT_SOURCE_DIR}/ObjectPoolTest.cpp)
target_link_libraries(ObjectPoolTest ObjectPool gtest_main)
create_test(ObjectPoolTest)
