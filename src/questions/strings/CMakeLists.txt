################################################################################
# Is Unique
################################################################################
add_executable(is_unique.test ${CMAKE_CURRENT_SOURCE_DIR}/is_unique.test.cpp)
target_link_libraries(is_unique.test gtest_main)
target_set_default_compiler_warnings(is_unique.test)
create_test(is_unique.test)

################################################################################
# Reverse C String
################################################################################
add_executable(
    reverse_c_string.test
    ${CMAKE_CURRENT_SOURCE_DIR}/reverse_c_string.test.cpp
)
target_link_libraries(reverse_c_string.test gtest_main)
target_set_default_compiler_warnings(reverse_c_string.test)
create_test(reverse_c_string.test)

################################################################################
# Check Permutation
################################################################################
add_executable(
    check_permutation.test
    ${CMAKE_CURRENT_SOURCE_DIR}/check_permutation.test.cpp
)
target_link_libraries(check_permutation.test gtest_main)
target_set_default_compiler_warnings(check_permutation.test)
create_test(check_permutation.test)

################################################################################
# URLify
################################################################################
add_executable(urlify.test ${CMAKE_CURRENT_SOURCE_DIR}/urlify.test.cpp)
target_link_libraries(urlify.test gtest_main)
target_set_default_compiler_warnings(urlify.test)
create_test(urlify.test)

################################################################################
# Palindrome Permutation
################################################################################
add_executable(
    palindrome_permutation.test
    ${CMAKE_CURRENT_SOURCE_DIR}/palindrome_permutation.test.cpp
)
target_link_libraries(palindrome_permutation.test gtest_main)
target_set_default_compiler_warnings(palindrome_permutation.test)
create_test(palindrome_permutation.test)

################################################################################
# One Away
################################################################################
add_executable(one_away.test ${CMAKE_CURRENT_SOURCE_DIR}/one_away.test.cpp)
target_link_libraries(one_away.test gtest_main)
target_set_default_compiler_warnings(one_away.test)
create_test(one_away.test)

################################################################################
# String Compression
################################################################################
add_executable(
    string_compression.test
    ${CMAKE_CURRENT_SOURCE_DIR}/string_compression.test.cpp
)
target_link_libraries(string_compression.test gtest_main)
target_set_default_compiler_warnings(string_compression.test)
create_test(string_compression.test)

################################################################################
# String Rotation
################################################################################
add_executable(
    string_rotation.test
    ${CMAKE_CURRENT_SOURCE_DIR}/string_rotation.test.cpp
)
target_link_libraries(string_rotation.test gtest_main)
target_set_default_compiler_warnings(string_rotation.test)
create_test(string_rotation.test)

################################################################################
# to_int
################################################################################
add_executable(to_int.test ${CMAKE_CURRENT_SOURCE_DIR}/to_int.test.cpp)
target_link_libraries(to_int.test gtest_main)
target_set_default_compiler_warnings(to_int.test)
target_executable_enable_ubisan(to_int.test)
create_test(to_int.test)
