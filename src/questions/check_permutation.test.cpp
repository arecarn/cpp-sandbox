// Check Permutation: Given two strings, write a method to decide if one is a
// permutation of the other.

#include<gtest/gtest.h>
#include <unordered_map>
#include <vector>
#include <iostream>

bool check_permutation(const std::string& s1, const std::string& s2)
{
    std::unordered_map<char, int> check;

    if (s1.size() != s2.size()) {
        return false;
    }

    for(char c: s1)
    {
        check[c]++;
    }

    for(char c: s2)
    {
        check[c]--;
    }

    for(const auto& e: check)
    {
        if (e.second != 0) {
            return false;
        }
    }

    return true;
}

struct TestCase
{
    std::string s1;
    std::string s2;
    bool result;
};

std::vector<TestCase> g_test_vector = {
    {"abc",    "bca",    true},
    {"abc",    "ba",     false},
    {"bczll",  "bllzc",  true},
    {"bczll",  "blczc",  false},
    {"zywp",   "pywz",   true},
    {"zxywp",  "pywzz",  false},
};


TEST(check_permutation, test)
{
    for (const auto& c  : g_test_vector)
    {
        std::cerr <<
            "Testing Strings: \"" << c.s1 << "\" and \"" << c.s2 << "\"\n";
        ASSERT_EQ(check_permutation(c.s1, c.s2), c.result);
    }
}

