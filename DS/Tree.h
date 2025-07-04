#pragma once

#include "Vector.h"

namespace dsa
{
struct TreeNode
{
    int       val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const int val);
};

namespace Tree
{
    dsa::TreeNode* insert_left(dsa::TreeNode* node,
                               const int      val);
    dsa::TreeNode* insert_right(dsa::TreeNode* node,
                                const int      val);

    void preorder(const dsa::TreeNode* node,
                  dsa::Vector<int>&    orders);
    void inorder(const dsa::TreeNode* node,
                 dsa::Vector<int>&    orders);
    void postorder(const dsa::TreeNode* node,
                   dsa::Vector<int>&    orders);

    dsa::Vector<dsa::Vector<int>> layerorder(const dsa::TreeNode* node);

    void clear_tree(dsa::TreeNode* root);
} // namespace Tree
} // namespace dsa
