#include "list_node.hpp"
#include <gtest/gtest.h>
#include <memory>

void insert_helper(std::shared_ptr<ListNode<int>>& node, std::shared_ptr<ListNode<int>>& new_node)
{

    if (node != nullptr)
    {
        node->next = new_node;
        new_node = new_node->next;
        node = node->next;
    }
    else
    {
        node = new_node;
        new_node = new_node->next;
    }
}

std::shared_ptr<ListNode<int>> merged_two_sorted_lists(std::shared_ptr<ListNode<int>>& l1, std::shared_ptr<ListNode<int>>& l2)
{
    std::shared_ptr<ListNode<int>> result;
    auto& result_head = result;

    while (l1 != nullptr && l2 != nullptr)
    {
        if (l1->data < l2->data)
        {
            insert_helper(result, l1);
        }
        else
        {
            insert_helper(result, l2);
        }
    }

    // insert the rest of the remaining list
    insert_helper(
        result,
        (l1 != nullptr) ? l1 : l2);

    return result_head;
}

TEST(merged_two_sorted_lists, when_lists_are_equal)
{
    auto l1 = make_list({1, 2, 3, 4, 5});
    auto l2 = make_list({1, 2, 3, 4, 5});

    auto result = merged_two_sorted_lists(l1, l2);
    auto expected = make_list({1, 1, 2, 2, 3, 3, 4, 4, 5, 5});
    ASSERT_TRUE(result == expected);
}

TEST(merged_two_sorted_lists, when_one_list_is_empty)
{
    auto l1 = make_list({1, 2, 3, 4, 5});
    auto l2 = make_list(std::initializer_list<int> {});

    auto result = merged_two_sorted_lists(l1, l2);
    auto expected = make_list({1, 2, 3, 4, 5});
    ASSERT_TRUE(result == expected);
}

TEST(merged_two_sorted_lists, when_one_list_shorter_than_the_other)
{
    auto l1 = make_list({1, 2, 3, 4, 5});
    auto l2 = make_list({3, 4, 5});

    auto result = merged_two_sorted_lists(l1, l2);
    auto expected = make_list({1, 2, 3, 3, 4, 4, 5, 5});
    ASSERT_TRUE(result == expected);
}
