// Is Unique: Implement an algorithm to determine if a string has all unique
// characters. What if you cannot use additional data structures?

#include <gtest/gtest.h>
#include <set>
#include <string>
#include <vector>


struct Solution
{
    virtual bool is_unique(std::string str) = 0;
};

struct ArraySolution : Solution
{
    bool is_unique(std::string str) override
    {
        constexpr size_t Char_Values = 128; // assuming ascii
        int char_seen[Char_Values] = {0};

        for (const auto& c : str)
        {
            if (char_seen[c] > 0)
            {
                return false;
            }
            char_seen[c]++;
        }
        return true;
    }
};

struct SetSolution : Solution
{
    bool is_unique(std::string str) override
    {
        std::set<char> char_seen;

        for (const auto& c : str)
        {
            [[maybe_unused]] auto [_, inserted] = char_seen.insert(c);
            if (!inserted)
            {
                return false;
            }
        }
        return true;
    }
};

struct TestCase {
    std::string str;
    bool result;
};

std::vector<TestCase> g_test_cases = {
    {"abcdefg", true},
    {"abcdefgg", false},
    {"abcdefgG", true},
    {"0abcdefg", true},
    {"Aabcdefg", true},
    {"Aabbcdeffg", false},
};

void test(Solution&& s)
{
    for(const auto& c : g_test_cases)
    {
        std::cerr << "Testing String: \"" << c.str << "\"\n";
        if(c.result)
        {
            ASSERT_TRUE(s.is_unique(c.str));
        }
        else
        {
            ASSERT_FALSE(s.is_unique(c.str));
        }
    }
}

TEST(is_unique, test)
{
    test(SetSolution{});
    test(ArraySolution{});
}
