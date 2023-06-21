// String Compression: Implement a method to perform basic string compression
// using the counts of repeated characters. For example, the string aabcccccaaa
// would become a2blc5a3. If the "compressed" string would not become smaller
// than the original string, your method should return the original string. You
// can assume the string has only uppercase and lowercase letters (a - z).
#include <gtest/gtest.h>
#include <iostream>
#include <string>

std::string string_compression(std::string str);
std::string string_compression(std::string str)
{
    std::string compressed_str;
    std::size_t i = 0;
    while (i < str.size())
    {
        std::size_t j {1};
        compressed_str.push_back(str[i]);
        while (i + j < str.size() && str[i] == str[i + j])
        {
            j++;
        }
        compressed_str.append(std::to_string(j));
        i += j;
    }
    if (compressed_str.size() >= str.size())
    {
        return str;
    }
    return compressed_str;
}

struct TestCase
{
    std::string input;
    std::string expected;
};

TestCase g_test_vector[] = {
    {"aabcccccaaa", "a2b1c5a3"},
    {"lldjssfffjkl", "lldjssfffjkl"},
};

TEST(string_compression, test)
{
    for (TestCase& c : g_test_vector)
    {
        std::cerr << "Testing String: \"" << c.input << "\"\n";
        std::string actual = string_compression(c.input);
        ASSERT_STREQ(actual.c_str(), c.expected.c_str());
    }
}
