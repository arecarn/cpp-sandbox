#include <fixed_vector.hpp>

#include <gtest/gtest.h>

TEST(fixed_vector, static)
{
    int a[3] {0, 1, 2};

    const FixedVector<int, 3> fixed_vector {a};

    int j = 0;
    for (auto i : fixed_vector)
    {
        ASSERT_EQ(j, i);
        j++;
    }
    ASSERT_EQ(j, 3);

    j = 0;
    for (const auto& i : fixed_vector)
    {
        ASSERT_EQ(j, i);
        j++;
    }
    ASSERT_EQ(j, 3);
}

TEST(fixed_vector, size)
{
    const int capcity {100};
    FixedVector<int, capcity> fixed_vector {};
    ASSERT_EQ(fixed_vector.size(), 0);
    ASSERT_EQ(fixed_vector.capacity(), capcity);

    // FixedVector {Array<int, 3> {{1, 2, 3}}};
}
