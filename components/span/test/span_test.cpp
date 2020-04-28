#include "span.hpp"
#include "array.hpp"

#include <gtest/gtest.h>

TEST(span, static) // NOLINT
{
    array<int, 3> array = {0, 1, 2};
    int c_array[5] = {0, 1, 2, 3, 4};

    span<int> c_array_span{c_array};

    span<int> array_span{array};


    int j = 0;
    for (auto i : c_array_span)
    {
        ASSERT_EQ(j, i);
        j++;
    }

    j = 0;
    for (const auto& i : array_span)
    {
        ASSERT_EQ(j, i);
        j++;
    }
}

TEST(span, size) // NOLINT
{
    const int array_size = 100;
    array<int, array_size> array = {};
    span<int> array_span(array);
    ASSERT_EQ(array_span.size(), array_size);
}
