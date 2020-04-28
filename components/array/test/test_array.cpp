#include <array.hpp>

#include <gtest/gtest.h>

TEST(array, static) // NOLINT
{
    const array<int, 3> array {0, 1, 2};

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

TEST(array, size) // NOLINT
{
    const int array_size = 100;
    array<int, array_size> array = {};
    ASSERT_EQ(array.size(), array_size);
}
