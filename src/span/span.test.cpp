#include "array.hpp"
#include "span.hpp"

#include <gtest/gtest.h>

TEST(span, static)
{
    Array<int, 3> array = {0, 1, 2};
    constexpr int C_Array_Size = 5;
    int c_array[C_Array_Size] = {0, 1, 2, 3, 4};

    Span<int> c_array_span {c_array};

    Span<int> array_span {array};

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

TEST(span, size)
{
    constexpr int Array_Size = 100;
    Array<int, Array_Size> array = {};
    Span<int> array_span(array);
    ASSERT_EQ(array_span.size(), Array_Size);
}
