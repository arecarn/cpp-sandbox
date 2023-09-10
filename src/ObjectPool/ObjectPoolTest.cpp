#include <ObjectPool.hpp>
#include <array>
#include <gtest/gtest.h>
#include <vector>

TEST(pool, static)
{
    ObjectPool<int, 5> pool;
    auto i = pool.make_unique(5);
    ASSERT_EQ(*i, 5);
    auto f = [](auto u) -> decltype(auto) { return u; };
    auto u = f(std::move(i));
    ASSERT_EQ(*u, 5);

    ObjectPool<std::array<int, 5>, 5> apool;
    auto a = apool.make_unique(1, 2, 3, 4, 5);
    ASSERT_EQ((*a)[0], 1);
    ASSERT_EQ((*a)[1], 2);
    ASSERT_EQ((*a)[2], 3);
    ASSERT_EQ((*a)[3], 4);
    ASSERT_EQ((*a)[4], 5);

    ObjectPool<std::vector<int>, 5> vpool;
    auto v = vpool.make_unique(1, 2, 3, 4, 5);
    ASSERT_EQ((*v)[0], 1);
    ASSERT_EQ((*v)[1], 2);
    ASSERT_EQ((*v)[2], 3);
    ASSERT_EQ((*v)[3], 4);
    ASSERT_EQ((*v)[4], 5);
    ASSERT_EQ((v->size()), 5);
}
