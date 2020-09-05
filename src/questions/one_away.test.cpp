// One Away: There are three types of edits that can be performed on strings: insert a character,
// remove a character, or replace a character. Given two strings, write a function to check if they are
// one edit (or zero edits) away.
// EXAMPLE
// pale, ple -> true
// pales,  pale -> true
// pale, bale -> true
// pale, bake -> false

#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <vector>

bool one_away(std::string s1, std::string s2)
{

    if (s1.size() == s2.size())
    {
        if (s1 == s2)
        {
            return true;
        }

        // check if only different by one character
        int diff_count = 0;
        for (int i = 0; i < s1.size(); i++)
        {
            if (s1[i] != s2[i])
            {
                diff_count++;
            }
        }
        if (diff_count == 1)
        {
            return true;
        }
    }
    else if (s1.size() == s2.size() - 1)
    {
        // check if s1 needs a character added
        // check if s2 needs a character removed
        int diff_count = 0;
        for (int i = 0; i < s2.size(); i++)
        {
            if (s2[i] != s1[i + diff_count])
            {
                diff_count++;
            }
            if (diff_count > 1)
            {
                break;
            }
            return true;
        }
    }
    else if (s1.size() == s2.size() + 1)
    {
        // check if s1 needs a character removed
        // check if s2 needs a character added
        int diff_count = 0;
        for (int i = 0; i < s1.size(); i++)
        {
            if (s1[i] != s2[i + diff_count])
            {
                diff_count++;
            }
            if (diff_count > 1)
            {
                break;
            }
            return true;
        }
    }
    return false;
}

struct TestCase
{
    std::string s1;
    std::string s2;
    bool result;
};

std::vector<TestCase> g_test_vector = {
    {"pale", "ple", true},
    {"pales", "pale", true},
    {"pale", "bale", true},
    {"pale", "bake", false},
};

TEST(one_away, test)
{
    for (const auto& c : g_test_vector)
    {
        std::cerr << "Testing Strings: \"" << c.s1 << "\" and \"" << c.s2 << "\"\n";
        ASSERT_EQ(one_away(c.s1, c.s2), c.result);
    }
}
