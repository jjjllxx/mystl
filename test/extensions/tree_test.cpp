#include "mystl/vector.h"
#include "extensions/tree.h"

#include "gtest/gtest.h"

namespace ext_test
{
namespace tree
{
    ext::tree_node* root  = new ext::tree_node { 5 };
    ext::tree_node* node3 = ext::tree::insert_left(root, 3);
    ext::tree_node* node2 = ext::tree::insert_right(root, 2);
    ext::tree_node* node6 = ext::tree::insert_right(node3, 6);
    ext::tree_node* node8 = ext::tree::insert_left(node2, 8);
    ext::tree_node* node9 = ext::tree::insert_left(node8, 9);

    ext::tree_node* node1 = ext::tree::insert_right(node9, 1);
    ext::tree_node* node4 = ext::tree::insert_right(node6, 4);
    ext::tree_node* node7 = ext::tree::insert_left(node3, 7);
} // namespace tree
} // namespace ext_test

GTEST_TEST(ext_tree, insert_left)
{
    ext::tree_node* root = new ext::tree_node { 5 };

    const ext::tree_node* left = ext::tree::insert_left(root, 3);
    EXPECT_EQ(left, root->left);
    EXPECT_EQ(left->val, 3);

    const ext::tree_node* newLeft = ext::tree::insert_left(root, 8);
    EXPECT_EQ(newLeft, root->left);
    EXPECT_EQ(newLeft->val, 8);

    EXPECT_EQ(ext::tree::insert_left(nullptr, 4), nullptr);

    ext::tree::clear_tree(root);
}

GTEST_TEST(ext_tree, insert_right)
{
    ext::tree_node* root = new ext::tree_node { 5 };

    const ext::tree_node* right = ext::tree::insert_right(root, 3);
    EXPECT_EQ(right, root->right);
    EXPECT_EQ(right->val, 3);

    const ext::tree_node* newRight = ext::tree::insert_right(root, 8);
    EXPECT_EQ(newRight, root->right);
    EXPECT_EQ(newRight->val, 8);

    EXPECT_EQ(ext::tree::insert_right(nullptr, 4), nullptr);

    ext::tree::clear_tree(root);
}

GTEST_TEST(ext_tree, preorder)
{
    mystl::vector<int> order;
    ext::tree::preorder(ext_test::tree::root, order);
    const mystl::vector<int> ans = { 5, 3, 7, 6, 4, 2, 8, 9, 1 };
    for (mystl::size_t i = 0; i < order.size(); ++i)
    {
        EXPECT_EQ(order[i], ans[i]);
    }
}

GTEST_TEST(ext_tree, inorder)
{
    mystl::vector<int> order;
    ext::tree::inorder(ext_test::tree::root, order);
    const mystl::vector<int> ans = { 7, 3, 6, 4, 5, 9, 1, 8, 2 };
    for (mystl::size_t i = 0; i < order.size(); ++i)
    {
        EXPECT_EQ(order[i], ans[i]);
    }
}

GTEST_TEST(ext_tree, postorder)
{
    mystl::vector<int> order;
    ext::tree::postorder(ext_test::tree::root, order);
    const mystl::vector<int> ans = { 7, 4, 6, 3, 1, 9, 8, 2, 5 };
    for (mystl::size_t i = 0; i < order.size(); ++i)
    {
        EXPECT_EQ(order[i], ans[i]);
    }
}

GTEST_TEST(ext_tree, layerorder)
{
    const mystl::vector<mystl::vector<int>> order = ext::tree::layerorder(ext_test::tree::root);
    EXPECT_EQ(order[0][0], 5);
    EXPECT_EQ(order[1][0], 3);
    EXPECT_EQ(order[1][1], 2);
    EXPECT_EQ(order[2][0], 7);
    EXPECT_EQ(order[2][1], 6);
    EXPECT_EQ(order[2][2], 8);
    EXPECT_EQ(order[3][0], 4);
    EXPECT_EQ(order[3][1], 9);
    EXPECT_EQ(order[4][0], 1);

    ext::tree::clear_tree(ext_test::tree::root);
}