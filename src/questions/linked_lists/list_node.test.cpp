#include "list_node.hpp"
#include <gtest/gtest.h>

TEST(list_node_utils, test_make_list_and_operators)
{
    auto l1 = make_list({1, 2, 3, 4, 5});
    auto l2 = make_list({1, 2, 3, 4, 5});
    auto l3 = make_list({1, 2, 3});
    ASSERT_TRUE(l1 == l2);
    ASSERT_FALSE(l1 == l3);
    ASSERT_FALSE(l1 != l2);
    ASSERT_TRUE(l1 != l3);
}
