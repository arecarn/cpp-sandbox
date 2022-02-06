// Palindrome Permutation: Given a string, write a function to check if it is a
// permutation of a palin­ drome. A palindrome is a word or phrase that is the
// same forwards and backwards. A permutation is a rearrangement of letters. The
// palindrome does not need to be limited to just dictionary words.
// EXAMPLE
// Input: Tact Coa
// Output: True (permutations: "taco cat", "atco eta", etc.)

#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

bool palindrome_permutation(const std::string& str)
{
    std::unordered_map<char, int> count {};

    auto is_char = [](char c) {
        return (c > 'a' && c < 'z') || (c > 'A' && c < 'Z');
    };

    auto is_even = [](int i) {
        return i % 2 == 0;
    };

    bool result = true;
    for (const auto& c : str)
    {
        if (is_char(c))
        {
            count[c]++;
            result = is_even(count[c]);
        }
    }

    return result;
}

struct TestCase
{
    std::string str;
    bool result;
};

std::vector<TestCase> g_test_vector = {
    {"abc", false},
    {"add", true},
    {"rce caar", true},
    {"toddraseseareddot", true},
    {"ana n", true},
    {"bannana", false},
    {"shool", false},
};

TEST(check_permutation, test)
{
    for (const auto& c : g_test_vector)
    {
        std::cerr << "Testing Strings: \"" << c.str << "\"\n";
        ASSERT_EQ(palindrome_permutation(c.str), c.result);
    }
}
