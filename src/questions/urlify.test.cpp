// URLify: Write a method to replace all spaces in a string with '%20'. You may
// assume that the string has sufficient space at the end to hold the
// additional characters, and that you are given the "true" length of the
// string. (Note: If implementing in Java, please use a character array so that
// you can perform this operation in place.)
// EXAMPLE
// ", 13
// Input:  "Mr John Smith    "
// Output: "Mr%20John%20Smith"

#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <cassert>

void urlify(char* str, int len)
{
    int index = len-1;
    int back_index = index;
    // walk backwards and find the first non-space
    while (str[index] == ' ' && index >= 0)
    {
        index--;
    }

    // copy non-spaces to the back of the string
    // when a space is encountered copy a %20 instead of a space
    while (index >= 0)
    {
        if(str[index] == ' ')
        {
            str[back_index] = '0';
            back_index--;
            str[back_index] = '2';
            back_index--;
            str[back_index] = '%';
            back_index--;
        }
        else
        {
            str[back_index] = str[index];
            back_index--;
        }
        index--;
    }

}

struct TestCase
{
    static constexpr int Buff_Size = 100;
    char str[Buff_Size];
    char result[Buff_Size];
    size_t len;
};

TestCase g_test_vector[] = {
    {"a b c    ", "a%20b%20c", 9}, // NOLINT
    {"can you spell my name        ", "can%20you%20spell%20my%20name", 29}, // NOLINT
};

TEST(Urlify, test) // NOLINT
{
    for (TestCase& c : g_test_vector)
    {
        std::cerr << "Testing String: \"" << c.str << "\"\n";
        urlify(c.str, c.len);
        ASSERT_STREQ(c.str, c.result);
    }
};
