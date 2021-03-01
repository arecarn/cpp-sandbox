// Return Kth to Last: Implement an algorithm to find the kth to last element of
// a singly linked list.
//
// NOTE: in this solution 0th to the last is the last element

#include <forward_list>
#include <gtest/gtest.h>

template <typename T>
T kth_to_last(std::forward_list<T> list, size_t kth)
{
    auto a = list.begin();
    auto b = list.begin();
    size_t count = 0;

    while (a != list.end())
    {
        if (count >= kth + 1)
        {
            b++;
        }
        a++;
        count++;
    }

    return *b;
}

TEST(kth_to_last, test)
{
    std::forward_list<int> fl{1, 2, 3, 4};
    ASSERT_EQ(4, kth_to_last(fl, 0));
    ASSERT_EQ(3, kth_to_last(fl, 1));
}
