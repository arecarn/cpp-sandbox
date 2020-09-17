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
    else
    {
        // check if one needs a character removed or if two needs a character added
        auto one_needs_rm_or_two_needs_add = [](std::string one, std::string two) {
            if (one.size() + 1 == two.size())
            {
                int diff_count = 0;
                for (int i = 0; i < two.size(); i++)
                {
                    if (two[i] != one[i + diff_count])
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
        };

        return one_needs_rm_or_two_needs_add(s1, s2)
            || one_needs_rm_or_two_needs_add(s2, s1);
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
