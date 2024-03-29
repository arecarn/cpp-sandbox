################################################################################
# Is Unique
################################################################################
add_executable(is_unique.test ${CMAKE_CURRENT_SOURCE_DIR}/is_unique.test.cpp)
target_link_libraries(is_unique.test gtest_main)

create_test(is_unique.test)

################################################################################
# Reverse C String
################################################################################
add_executable(
    reverse_c_string.test
    ${CMAKE_CURRENT_SOURCE_DIR}/reverse_c_string.test.cpp
)
target_link_libraries(reverse_c_string.test gtest_main)

create_test(reverse_c_string.test)

################################################################################
# Check Permutation
################################################################################
add_executable(
    check_permutation.test
    ${CMAKE_CURRENT_SOURCE_DIR}/check_permutation.test.cpp
)
target_link_libraries(check_permutation.test gtest_main)

create_test(check_permutation.test)

################################################################################
# URLify
################################################################################
add_executable(urlify.test ${CMAKE_CURRENT_SOURCE_DIR}/urlify.test.cpp)
target_link_libraries(urlify.test gtest_main)

create_test(urlify.test)

################################################################################
# Palindrome Permutation
################################################################################
add_executable(
    palindrome_permutation.test
    ${CMAKE_CURRENT_SOURCE_DIR}/palindrome_permutation.test.cpp
)
target_link_libraries(palindrome_permutation.test gtest_main)

create_test(palindrome_permutation.test)

################################################################################
# One Away
################################################################################
add_executable(one_away.test ${CMAKE_CURRENT_SOURCE_DIR}/one_away.test.cpp)
target_link_libraries(one_away.test gtest_main)

create_test(one_away.test)

################################################################################
# String Compression
################################################################################
add_executable(
    string_compression.test
    ${CMAKE_CURRENT_SOURCE_DIR}/string_compression.test.cpp
)
target_link_libraries(string_compression.test gtest_main)

create_test(string_compression.test)

################################################################################
# String Rotation
################################################################################
add_executable(
    string_rotation.test
    ${CMAKE_CURRENT_SOURCE_DIR}/string_rotation.test.cpp
)
target_link_libraries(string_rotation.test gtest_main)

create_test(string_rotation.test)

################################################################################
# to_int
################################################################################
add_executable(to_int.test ${CMAKE_CURRENT_SOURCE_DIR}/to_int.test.cpp)
target_link_libraries(to_int.test gtest_main)

create_test(to_int.test)

################################################################################
# to_string
################################################################################
add_executable(to_string.test ${CMAKE_CURRENT_SOURCE_DIR}/to_string.test.cpp)
target_link_libraries(to_string.test gtest_main)

create_test(to_string.test)
