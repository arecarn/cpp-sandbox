#include <array.hpp>

#include <gtest/gtest.h>

TEST(array, static)
{
    const Array<int, 3> array{0, 1, 2};

    int j = 0;
    for (auto i : array)
    {
        ASSERT_EQ(j, i);
        j++;
    }
    ASSERT_EQ(j, 3);

    j = 0;
    for (const auto& i : array)
    {
        ASSERT_EQ(j, i);
        j++;
    }
    ASSERT_EQ(j, 3);
}

TEST(array, size)
{
    const int array_size = 100;
    Array<int, array_size> array = {};
    ASSERT_EQ(array.size(), array_size);
}
