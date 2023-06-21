#include <gtest/gtest.h>
#include <string>

namespace
{

std::string to_string(int a_int)
{
    std::string result;

    int i {a_int};
    do
    {
        int num = abs(i % 10);
        i = i / 10;
        auto c = static_cast<char>(num + '0');
        result.push_back(c);
    } while (i != 0);

    if (a_int < 0)
    {
        result.push_back('-');
    }

    return {result.rbegin(), result.rend()};
}

TEST(to_string, test)
{
    ASSERT_EQ(to_string(42), "42");
    ASSERT_EQ(to_string(0), "0");
    ASSERT_EQ(to_string(-123), "-123");
    ASSERT_EQ(to_string(std::numeric_limits<int>::min()), "-2147483648");
    ASSERT_EQ(to_string(std::numeric_limits<int>::max()), "2147483647");
}

} // namespace
