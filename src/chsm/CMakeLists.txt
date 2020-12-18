################################################################################
# Library
################################################################################
add_library(chsm INTERFACE)
target_include_directories(chsm INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_set_default_compiler_warnings(chsm)

################################################################################
# Independent Compilation Test
################################################################################
add_library(chsm.compile.test STATIC ${CMAKE_CURRENT_SOURCE_DIR}/chsm.cpp)
target_link_libraries(chsm)
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
