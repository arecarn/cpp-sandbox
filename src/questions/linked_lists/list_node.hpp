#include <memory>
#include <string>

template <typename T>
struct ListNode
{
    T data;
    std::shared_ptr<ListNode<T>> next;
};

template <typename T>
std::shared_ptr<ListNode<T>> make_list(std::initializer_list<T> il)
{
    auto dummy_head = std::make_shared<ListNode<T>>();
    auto tail = dummy_head;
    if (il.size() != 0)
    {
        auto i = il.begin();
        while (i != il.end())
        {
            auto n = std::make_shared<ListNode<T>>();
            tail->next = n;
            n->data = *i;
            tail = tail->next;
            i++;
        }
    }

    return dummy_head->next;
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
    auto p1 = l1;
    auto p2 = l2;
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

template <typename T>
std::string to_string(std::shared_ptr<ListNode<T>>& l)
{
    std::string result;
    result.push_back('{');
    while (l != nullptr)
    {
        result.append(std::to_string(l->data));
        result.push_back(',');
        l = l->next;
    }
    result.push_back('}');
    return result;
}
