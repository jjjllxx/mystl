#include "DS/Tree.h"
#include "DS/Vector.h"

#include "gtest/gtest.h"
#include <cstddef>

namespace dsa_test
{
namespace Tree
{
    dsa::TreeNode* root  = new dsa::TreeNode { 5 };
    dsa::TreeNode* node3 = dsa::Tree::insert_left(root, 3);
    dsa::TreeNode* node2 = dsa::Tree::insert_right(root, 2);
    dsa::TreeNode* node6 = dsa::Tree::insert_right(node3, 6);
    dsa::TreeNode* node8 = dsa::Tree::insert_left(node2, 8);
    dsa::TreeNode* node9 = dsa::Tree::insert_left(node8, 9);

    dsa::TreeNode* node1 = dsa::Tree::insert_right(node9, 1);
    dsa::TreeNode* node4 = dsa::Tree::insert_right(node6, 4);
    dsa::TreeNode* node7 = dsa::Tree::insert_left(node3, 7);
} // namespace Tree
} // namespace dsa_test

GTEST_TEST(DS_Tree, insert_left)
{
    dsa::TreeNode* root = new dsa::TreeNode { 5 };

    const dsa::TreeNode* left = dsa::Tree::insert_left(root, 3);
    EXPECT_EQ(left, root->left);
    EXPECT_EQ(left->val, 3);

    const dsa::TreeNode* newLeft = dsa::Tree::insert_left(root, 8);
    EXPECT_EQ(newLeft, root->left);
    EXPECT_EQ(newLeft->val, 8);

    EXPECT_EQ(dsa::Tree::insert_left(nullptr, 4), nullptr);

    dsa::Tree::clear_tree(root);
}

GTEST_TEST(DS_Tree, insert_right)
{
    dsa::TreeNode* root = new dsa::TreeNode { 5 };

    const dsa::TreeNode* right = dsa::Tree::insert_right(root, 3);
    EXPECT_EQ(right, root->right);
    EXPECT_EQ(right->val, 3);

    const dsa::TreeNode* newRight = dsa::Tree::insert_right(root, 8);
    EXPECT_EQ(newRight, root->right);
    EXPECT_EQ(newRight->val, 8);

    EXPECT_EQ(dsa::Tree::insert_right(nullptr, 4), nullptr);

    dsa::Tree::clear_tree(root);
}

GTEST_TEST(DS_Tree, preorder)
{
    dsa::Vector<int> order;
    dsa::Tree::preorder(dsa_test::Tree::root, order);
    const dsa::Vector<int> ans = { 5, 3, 7, 6, 4, 2, 8, 9, 1 };
    for (std::size_t i = 0; i < order.size(); ++i)
    {
        EXPECT_EQ(order[i], ans[i]);
    }
}

GTEST_TEST(DS_Tree, inorder)
{
    dsa::Vector<int> order;
    dsa::Tree::inorder(dsa_test::Tree::root, order);
    const dsa::Vector<int> ans = { 7, 3, 6, 4, 5, 9, 1, 8, 2 };
    for (std::size_t i = 0; i < order.size(); ++i)
    {
        EXPECT_EQ(order[i], ans[i]);
    }
}

GTEST_TEST(DS_Tree, postorder)
{
    dsa::Vector<int> order;
    dsa::Tree::postorder(dsa_test::Tree::root, order);
    const dsa::Vector<int> ans = { 7, 4, 6, 3, 1, 9, 8, 2, 5 };
    for (std::size_t i = 0; i < order.size(); ++i)
    {
        EXPECT_EQ(order[i], ans[i]);
    }
}

GTEST_TEST(DS_Tree, layerorder)
{
    const dsa::Vector<dsa::Vector<int>> order = dsa::Tree::layerorder(dsa_test::Tree::root);
    EXPECT_EQ(order[0][0], 5);
    EXPECT_EQ(order[1][0], 3);
    EXPECT_EQ(order[1][1], 2);
    EXPECT_EQ(order[2][0], 7);
    EXPECT_EQ(order[2][1], 6);
    EXPECT_EQ(order[2][2], 8);
    EXPECT_EQ(order[3][0], 4);
    EXPECT_EQ(order[3][1], 9);
    EXPECT_EQ(order[4][0], 1);

    dsa::Tree::clear_tree(dsa_test::Tree::root);
}