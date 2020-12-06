#include <memory>

template <typename T>
struct BinaryTreeNode
{
    T data;
    std::unique_ptr<BinaryTreeNode<T>> left;
    std::unique_ptr<BinaryTreeNode<T>> right;
};

template <typename T>
std::unique_ptr<BinaryTreeNode<T>> make_binary_tree_node(T x)
{
    return std::make_unique<BinaryTreeNode<T>>(x);
}
