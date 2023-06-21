// Implement to_int which converts a string to an integer.
//
// The function first discards as many whitespace characters as necessary until
// the first non-whitespace character is found. Then, starting from this
// character, takes an optional initial plus or minus sign followed by as many
// numerical digits as possible, and interprets them as a numerical value.
//
// The string can contain additional characters after those that form the
// integral number, which are ignored and have no effect on the behavior of this
// function.
//
// If the first sequence of non-whitespace characters in str is not a valid
// integral number, or if no such sequence exists because either str is empty or
// it contains only whitespace characters, no conversion is performed.
//
// If no valid conversion could be performed, a zero value is returned.
//
// Note:
// Only the space character ' ' is considered as whitespace character.  Assume
// we are dealing with an environment which could only store integers within the
// 32-bit signed integer range: [−231,  231 − 1]. If the numerical value is out
// of the range of representable values, INT_MAX (231 − 1) or INT_MIN (−231) is
// returned.
//
// Example 1:
// Input: "42"
// Output: 42

// Example 2:
// Input: "   -42"
// Output: -42
// Explanation: The first non-whitespace character is '-', which is the minus
// sign. Then take as many numerical digits as possible, which gets 42.
//
// Example 3:
// Input: "4193 with words"
// Output: 4193
// Explanation: Conversion stops at digit '3' as the next character is not a
// numerical digit.
//
// Example 4:
// Input: "words and 987"
// Output: 0
// Explanation: The first non-whitespace character is 'w', which is not a
// numerical digit or a +/- sign. Therefore no valid conversion could be
// performed.
//
// Example 5:
// Input: "-91283472332"
// Output: -2147483648
// Explanation: The number "-91283472332" is out of the range of a 32-bit signed
// integer. Therefore INT_MIN (−2147483648) is returned.

#include <cctype>
#include <gtest/gtest.h>
#include <limits>
#include <string>

int to_int(std::string s);

int to_int(std::string s)
{
    int result = 0;
    size_t i {0};

    while (s[i] == ' ' || s[i] == '\t')
    {
        i++;
    }

    int sign {1};
    if (s[i] == '-')
    {
        sign = -1;
        i++;
    }
    else if (s[i] == '+')
    {
        i++;
    }

    while (i != s.size() && std::isdigit(s[i]))
    {
        if (result <= std::numeric_limits<int>::max() / 10)
        {
            result *= 10;
        }
        else
        {
            return (sign > 0) ? std::numeric_limits<int>::max()
                              : std::numeric_limits<int>::min();
        }

        int num = (s[i] - '0');
        if (result <= std::numeric_limits<int>::max() - num)
        {
            result += num;
        }
        else
        {
            return (sign > 0) ? std::numeric_limits<int>::max()
                              : std::numeric_limits<int>::min();
        }
        i++;
    }

    return result * sign;
}

TEST(to_int, convert_positive_int_string_to_an_int)
{
    ASSERT_EQ(to_int("42"), 42);
}

TEST(to_int, convert_positive_int_with_leading_zero_string_to_an_int)
{
    ASSERT_EQ(to_int("042"), 42);
}

TEST(to_int, convert_positive_int_with_leading_plus_string_to_an_int)
{
    ASSERT_EQ(to_int("+123"), 123);
}

TEST(to_int,
    convert_positive_int_with_leading_plus_and_leading_zero_string_to_an_int)
{
    ASSERT_EQ(to_int("+000123"), 123);
}

TEST(to_int, convert_negative_int_string_to_an_int)
{
    ASSERT_EQ(to_int("-7832"), -7832);
}

TEST(to_int, convert_negative_int_with_leading_zero_string_to_an_int)
{
    ASSERT_EQ(to_int("-007832"), -7832);
}

TEST(to_int, return_int_min_for_an_int_string_that_is_too_small)
{
    ASSERT_EQ(to_int("-999999999999999999"), std::numeric_limits<int>::min());
}

TEST(to_int, return_int_max_for_an_int_string_that_is_too_large)
{
    ASSERT_EQ(to_int("4294967111111111111"), std::numeric_limits<int>::max());
}

TEST(to_int, return_zero_for_an_invalid_string)
{
    ASSERT_EQ(to_int("this won't work 55"), 0);
}

TEST(to_int, return_number_given_trailing_text)
{
    ASSERT_EQ(to_int("55 this will work"), 55);
}

TEST(to_int, max_int_string)
{
    auto max_int_str = std::to_string(std::numeric_limits<int>::max());
    ASSERT_EQ(to_int(max_int_str), std::numeric_limits<int>::max());
}

TEST(to_int, min_int_string)
{
    auto min_int_str = std::to_string(std::numeric_limits<int>::min());
    ASSERT_EQ(to_int(min_int_str), std::numeric_limits<int>::min());
}
