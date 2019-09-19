#include <array.hpp>

#include <gtest/gtest.h>

TEST(ArrayTest, Static) // NOLINT
{
    const array<int, 3> array = {0, 1, 2};

    int j = 0;
    for (auto i : array)
    {
        ASSERT_EQ(j, i);
        j++;
    }

    j = 0;
    for (const auto& i : array)
    {
        ASSERT_EQ(j, i);
        j++;
    }
}
