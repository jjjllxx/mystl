#pragma once

#include "mystl/vector.h"

namespace ext
{
struct tree_node
{
    int       val;
    tree_node* left;
    tree_node* right;

    tree_node(const int val);
};

namespace tree
{
    tree_node* insert_left(tree_node* node,
                               const int      val);
    tree_node* insert_right(tree_node* node,
                                const int      val);

    void preorder(const tree_node* node,
                  mystl::vector<int>&    orders);
    void inorder(const tree_node* node,
                 mystl::vector<int>&    orders);
    void postorder(const tree_node* node,
                   mystl::vector<int>&    orders);

    mystl::vector<mystl::vector<int>> layerorder(const tree_node* node);

    void clear_tree(tree_node* root);
} // namespace tree
} // namespace ext
