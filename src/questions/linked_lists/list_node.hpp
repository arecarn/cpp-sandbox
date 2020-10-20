#include <memory>

template <typename T>
struct ListNode
{
    T data;
    std::shared_ptr<ListNode<T>> next;
};

template <typename T>
std::shared_ptr<ListNode<T>> make_list(std::initializer_list<T> il)
{
    std::shared_ptr<ListNode<T>> head;
    auto& ptr = head;
    if (il.size() != 0)
    {
        auto i = il.begin();
        ptr = std::make_shared<ListNode<T>>();
        ptr->data = *i;
        i++;
        while (i != il.end())
        {
            auto n = std::make_shared<ListNode<T>>();
            ptr->next = n;
            n->data = *i;
            ptr = ptr->next;
            i++;
        }
    }

    return head;
}

template <typename T>
void push_back(std::shared_ptr<ListNode<T>>& l, T value)
{
    if (l == nullptr)
    {
        l->value = value;
    }
    else
    {
        l->next = std::make_shared<ListNode<T>>;
    }
}

template <typename T>
bool operator==(const std::shared_ptr<ListNode<T>>& l1, const std::shared_ptr<ListNode<T>>& l2)
{
    auto p1 {l1};
    auto p2 {l2};
    while (p1 != nullptr && p2 != nullptr)
    {
        if (p1->data != p2->data)
        {
            return false;
        }
        p1 = p1->next;
        p2 = p2->next;
    }

    return p1 == nullptr && p2 == nullptr;
}

template <typename T>
bool operator!=(const std::shared_ptr<ListNode<T>>& l1, const std::shared_ptr<ListNode<T>>& l2)
{
    return !(l1 == l2);
}
