// Remove Dups: Write code to remove duplicates from an unsorted linked list.
// FOLLOW UP
// How would you solve this problem if a temporary buffer is not allowed?

#include <forward_list>
#include <gtest/gtest.h>
#include <iostream>
#include <unordered_map>

template <typename T>
void remove_dupes(std::forward_list<T>& list)
{
    if (list.empty())
    {
        return;
    }

    std::unordered_map<T, int> seen_count;
    auto f = list.begin();
    auto n = list.begin();
    n++;
    seen_count[*f]++;
    while (n != list.end())
    {
        seen_count[*n]++;
        if (seen_count[*n] > 1)
        {
            seen_count[*n]--;
            n = list.erase_after(f);
        }
        else
        {
            f++;
            n++;
        }
    }
}

TEST(remove_dupes, test)
{
    std::forward_list<int> fl {1, 1, 2, 2, 3, 3};
    remove_dupes(fl);
    std::forward_list<int> fle {1, 2, 3};
    ASSERT_EQ(fl, fle);
}

TEST(remove_dupes, with_a_single_element)
{
    std::forward_list<int> fl {1};
    remove_dupes(fl);
    std::forward_list<int> fle {1};
    ASSERT_EQ(fl, fle);
}

TEST(remove_dupes, when_empty)
{
    std::forward_list<int> fl {};
    remove_dupes(fl);
    std::forward_list<int> fle {};
    ASSERT_EQ(fl, fle);
}
