#include <algorithm>
#include <gtest/gtest.h>
#include <list>

template <typename T>
std::list<T> merged_two_sorted_lists(std::list<T> l1, std::list<T> l2)
{
    std::list<T> result;
    auto i1 = l1.begin();
    auto i2 = l2.begin();

    while (i1 != l1.end() && i2 != l2.end())
    {
        if (*i1 < *i2)
        {
            result.push_back(*i1);
            i1++;
        }
        else
        {
            result.push_back(*i2);
            i2++;
        }
    }

    if (i1 != l1.end())
    {
        std::copy(i1, l1.end(), std::back_inserter(result));
    }

    if (i2 != l2.end())
    {
        std::copy(i2, l2.end(), std::back_inserter(result));
    }

    return result;
}

TEST(test, list_1_and_2_are_the_same)
{
    std::list<int> l1 {1, 2, 3, 4, 5};
    std::list<int> l2 {1, 2, 3, 4, 5};

    std::list<int> result = merged_two_sorted_lists(l1, l2);
    const std::list<int> expected = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
    ASSERT_EQ(result, expected);
}

TEST(test, list_1_greater_than_list_2)
{
    std::list<int> l1 {1, 2, 3, 4, 5};
    std::list<int> l2 {1, 2, 3};

    std::list<int> result = merged_two_sorted_lists(l1, l2);
    const std::list<int> expected = {1, 1, 2, 2, 3, 3, 4, 5};
    ASSERT_EQ(result, expected);
}
