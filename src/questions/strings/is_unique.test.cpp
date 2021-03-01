// Is Unique: Implement an algorithm to determine if a string has all unique
// characters. What if you cannot use additional data structures?
//
// Solution Notes:
// * need to specify character set expected
// * specify some type of behavior if character in set is invalid
// * When assuming ASCII a array is just as handy as a std::set

#include <exception>
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
        constexpr size_t Char_Values = 128; // assuming ASCII
        bool char_seen[Char_Values] = {false};

        for (const auto& c : str)
        {
            if (c > Char_Values)
            {
                throw std::out_of_range("character is not ASCII");
            }
            if (char_seen[c])
            {
                return false;
            }
            char_seen[c] = true;
        }
        return true;
    }
};

struct SetSolution : Solution
{
    bool is_unique(std::string str) override
    {
        constexpr size_t Char_Values = 128; // assuming ASCII
        std::set<char> char_seen;

        for (const auto& c : str)
        {
            if (c > Char_Values)
            {
                throw std::out_of_range("character is not ASCII");
            }
            [[maybe_unused]] auto [_, inserted] = char_seen.insert(c);
            if (!inserted)
            {
                return false;
            }
        }
        return true;
    }
};

struct TestCase
{
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
    for (const auto& c : g_test_cases)
    {
        std::cerr << "Testing String: \"" << c.str << "\"\n";
        if (c.result)
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
