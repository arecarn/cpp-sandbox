#include "binary_tree_node.hpp"
#include <algorithm>

int height(std::unique_ptr<BinaryTreeNode<int>>& node)
{

    int left_height = 0;
    int right_height = 0;

    if (node->left == nullptr)
    {
        left_height = 1;
    }
    else
    {
        left_height = height(node->left);
    }

    if (node->right == nullptr)
    {
        left_height = 1;
    }
    else
    {
        right_height = height(node->right);
    }

    return std::max(left_height, right_height) + 1;
}

TEST(height, test)
{
    make_binary_tree_node(T x)
}
