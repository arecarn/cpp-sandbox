// Implement atoi which converts a string to an integer.
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

#include <gtest/gtest.h>
#include <limits>
#include <string>

enum class State
{
    Find_Non_White_Space,
    Find_Sign,
    Skip_Leading_Zeros,
    First_Digit,
    Convert,
};

int to_int(std::string str)
{
    auto is_num = [](char c) -> bool {
        return c >= '0' && c <= '9';
    };

    auto to_int = [](char c) -> int {
        return c - '0';
    };

    decltype(str.size()) i {0};
    int result = 0;
    int sign = 1;
    State state = State::Find_Non_White_Space;

    // walk past whitespace
    while (i < str.size())
    {
        switch (state)
        {
            case State::Find_Non_White_Space:

                if (str[i] == ' ' || str[i] == '\t')
                {
                    i++;
                    break;
                }
                state = State::Find_Sign;
                break;

            case State::Find_Sign:
                if (str[i] == '-')
                {
                    sign = -1;
                    i++;
                }
                else if (str[i] == '+')
                {
                    i++;
                }

            case State::Skip_Leading_Zeros:
                if (str[i] == '0')
                {
                    i++; // TODO test
                    break;
                }
                state = State::First_Digit;

            case State::First_Digit:
                if (is_num(str[i]))
                {
                    result = to_int(str[i]) * sign;
                }
                else
                {
                    return 0;
                }
                i++;
                state = State::Convert;
                break;

            case State::Convert:
                if (is_num(str[i]))
                {

                    int num = sign == -1 ? -to_int(str[i])
                                         : to_int(str[i]);
                    int new_result = result * 10 + num;
                    i++;

                    // check for overflow
                    if ((new_result - num) / 10 != result)
                    {
                        if (sign == -1)
                        {
                            return std::numeric_limits<int>::min();
                        }
                        return std::numeric_limits<int>::max();
                    }
                    result = new_result;
                }
                else
                {
                    return result;
                }
                break;
        }
    }
    return result;
}

TEST(atoi, convert_positive_int_string_to_an_int)
{
    ASSERT_EQ(to_int("42"), 42);
}

TEST(atoi, convert_positive_int_with_leading_zero_string_to_an_int)
{
    ASSERT_EQ(to_int("042"), 42);
}

TEST(atoi, convert_positive_int_with_leading_plus_string_to_an_int)
{
    ASSERT_EQ(to_int("+123"), 123);
}

TEST(atoi, convert_positive_int_with_leading_plus_and_leading_zero_string_to_an_int)
{
    ASSERT_EQ(to_int("+000123"), 123);
}

TEST(atoi, convert_negative_int_string_to_an_int)
{
    ASSERT_EQ(to_int("-7832"), -7832);
}

TEST(atoi, convert_negative_int_with_leading_zero_string_to_an_int)
{
    ASSERT_EQ(to_int("-007832"), -7832);
}

TEST(atoi, return_int_min_for_an_int_string_that_is_too_small)
{
    ASSERT_EQ(to_int("-999999999999999999"), std::numeric_limits<int>::min());
}

TEST(atoi, return_int_max_for_an_int_string_that_is_too_large)
{
    ASSERT_EQ(to_int("999999999999999999"), std::numeric_limits<int>::max());
}

TEST(atoi, return_zero_for_an_invalid_string)
{
    ASSERT_EQ(to_int("this won't work 55"), 0);
}
