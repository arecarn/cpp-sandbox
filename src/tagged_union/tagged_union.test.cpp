#include "tagged_union.hpp"
#include "gtest/gtest.h"

TEST(basic, pizza)
{
    constexpr int N = 5;
    Value v{N};
    ASSERT_EQ(*v.as_int(), N);

    constexpr int K = 6;
    v.as_int(K);
    ASSERT_EQ(*v.as_int(), K);

    constexpr float F = 5.5;
    v.as_float(F);
    ASSERT_EQ(*v.as_float(), F);
}
