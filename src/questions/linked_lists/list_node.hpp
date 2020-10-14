#include <memory>

template <typename T>
struct ListNode
{
    T data;
    std::shared_ptr<ListNode<T>> next;
};
