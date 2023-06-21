// Delete Middle Node: Implement an algorithm to delete a node in the middle
// (i.e., any node but the first and last node, not necessarily the exact
// middle) of a singly linked list, given only access to that node.
// EXAMPLE
// Input:the node c from the linked list a->b->c->d->e->f
// Result: nothing is returned, but the new linked list looks like a->b->d->e->f

#include <forward_list>
#include <gtest/gtest.h>

template <typename T>
void delete_middle_node(std::forward_list<T>& list)
{

    if (list.empty())
    {
        return;
    }

    // find size
    int size = 0;
    for ([[maybe_unused]] auto const& i : list)
    {
        size++;
    }

    if (size == 1)
    {
        list.clear();
    }
    else
    {
        auto c = 0;
        auto i = list.begin();
        for (; c != size / 2 - 1; c++, i++)
        {
        }
        list.erase_after(i);
    }
}

TEST(delete_middle_node, general_case)
{
    std::forward_list<int> fl {1, 2, 3, 4, 5};
    delete_middle_node(fl);
    std::forward_list<int> fle {1, 2, 4, 5};
    ASSERT_EQ(fl, fle);
}

TEST(delete_middle_node, with_a_single_element)
{
    std::forward_list<int> fl {1};
    delete_middle_node(fl);
    std::forward_list<int> fle {};
    ASSERT_EQ(fl, fle);
}

TEST(delete_middle_node, when_empty)
{
    std::forward_list<int> fl {};
    delete_middle_node(fl);
    std::forward_list<int> fle {};
    ASSERT_EQ(fl, fle);
}
