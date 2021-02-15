################################################################################
# Library
################################################################################
add_library(chsm STATIC ${CMAKE_CURRENT_SOURCE_DIR}/chsm.cpp)
target_include_directories(chsm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_set_default_compiler_warnings(chsm)

################################################################################
# Test
################################################################################
add_executable(
    chsm.test
    ${CMAKE_CURRENT_SOURCE_DIR}/chsm.test.cpp
)
target_link_libraries(chsm.test chsm gtest_main gmock)
create_test(chsm.test)
