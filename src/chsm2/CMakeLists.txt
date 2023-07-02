################################################################################
# Library
################################################################################
add_library(chsm2 STATIC ${CMAKE_CURRENT_SOURCE_DIR}/chsm.cpp)
target_include_directories(chsm2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

################################################################################
# Test
################################################################################
add_executable(chsm2.test ${CMAKE_CURRENT_SOURCE_DIR}/chsm.test.cpp)
target_link_libraries(chsm2.test chsm2 gtest_main gmock)
create_test(chsm2.test)
