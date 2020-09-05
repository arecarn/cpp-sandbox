// Palindrome Permutation: Given a string, write a function to check if it is a
// permutation of a palin­ drome. A palindrome is a word or phrase that is the
// same forwards and backwards. A permutation is a rearrangement of letters. The
// palindrome does not need to be limited to just dictionary words.
// EXAMPLE
// Input: Tact Coa
// Output: True (permutations: "taco cat", "atco eta", etc.)

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <iostream>

bool palindrome_permutation(std::string s)
{
    auto b = s.size()-1;
    decltype(b) f = 0;

    while (f < b)
    {
        if (s[f] != s[b])
        {
            return false;
        }
        f++;
        b--;
    }
    return true;
}

struct TestCase
{
    std::string str;
    bool result;
};

std::vector<TestCase> g_test_vector = {
    {"abc", false},
    {"dad", true},
    {"racecar", true},
    {"todderasesareddot", true},
    {"anna", true},
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
