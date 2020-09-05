// Write code to reverse a C-Style String. (C-String means that “abcd” is
// represented as five characters, including the null character.)
//
#include <gtest/gtest.h>
#include <iostream>

void reverse_c_string(char* str)
{
    char* start = str;
    char* end = str;

    // find end of str
    while (*end != '\0')
    {
        end++;
    }
    end--;

    while (start < end)
    {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

struct TestCase
{
    static constexpr int Buff_Size = 100;
    char str[Buff_Size];
    char result[Buff_Size];
};

TestCase g_test_cases[] = {
    {"abc", "cba"},
    {"cba", "abc"},
    {"this is a longer string", "gnirts regnol a si siht"},
    {"here's another test string", "gnirts tset rehtona s'ereh"},
};

TEST(reverse_c_string, test)
{
    for (TestCase& c : g_test_cases)
    {
        std::cerr << "Testing String: \"" << c.str << "\"\n";
        reverse_c_string(c.str);
        ASSERT_STREQ(c.str, c.result);
    }
};
