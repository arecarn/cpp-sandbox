#include "list_node.hpp"
#include <gtest/gtest.h>
#include <memory>

namespace
{
void insert_helper(std::shared_ptr<ListNode<int>>& tail, std::shared_ptr<ListNode<int>>& new_node)
{
    tail->next = new_node;
    tail = tail->next;
    new_node = new_node->next;
}

std::shared_ptr<ListNode<int>> merged_two_sorted_lists(std::shared_ptr<ListNode<int>>& l1, std::shared_ptr<ListNode<int>>& l2)
{
    auto dummy_head = std::make_shared<ListNode<int>>();
    auto tail = dummy_head;

    while (l1 != nullptr && l2 != nullptr)
    {
        insert_helper(tail,
            (l1->data <= l2->data) ? l1 : l2);
    }

    // insert the rest of the remaining list
    insert_helper(
        tail,
        (l1 != nullptr) ? l1 : l2);

    return dummy_head->next;
}
}

TEST(merged_two_sorted_lists, when_lists_are_equal)
{
    auto l1 = make_list({1, 2, 3, 4, 5});
    auto l2 = make_list({1, 2, 3, 4, 5});

    auto result = merged_two_sorted_lists(l1, l2);
    auto expected = make_list({1, 1, 2, 2, 3, 3, 4, 4, 5, 5});
    std::cerr << "result: " << to_string(result) << '\n';
    std::cerr << "expected: " << to_string(expected) << '\n';
    ASSERT_TRUE(result == expected);
}

TEST(merged_two_sorted_lists, when_one_list_is_empty)
{
    auto l1 = make_list({1, 2, 3, 4, 5});
    auto l2 = make_list(std::initializer_list<int> {});

    auto result = merged_two_sorted_lists(l1, l2);
    auto expected = make_list({1, 2, 3, 4, 5});
    std::cerr << "result: " << to_string(result) << '\n';
    std::cerr << "expected: " << to_string(expected) << '\n';
    ASSERT_TRUE(result == expected);
}

TEST(merged_two_sorted_lists, when_one_list_shorter_than_the_other)
{
    auto l1 = make_list({1, 2, 3, 4, 5});
    auto l2 = make_list({3, 4, 5});

    auto result = merged_two_sorted_lists(l1, l2);
    auto expected = make_list({1, 2, 3, 3, 4, 4, 5, 5});
    std::cerr << "result: " << to_string(result) << '\n';
    std::cerr << "expected: " << to_string(expected) << '\n';
    ASSERT_TRUE(result == expected);
}
