#include "DS/Vector.h"
#include "Others/BST.h"
#include "Others/Tree.h"

#include "gtest/gtest.h"
#include <stdexcept>

namespace dsa_test
{
namespace BST
{
    dsa::TreeNode* root  = new dsa::TreeNode { 5 };
    dsa::TreeNode* node3 = dsa::BST::insert(root, 3);
    dsa::TreeNode* node8 = dsa::BST::insert(root, 8);
    dsa::TreeNode* node2 = dsa::BST::insert(root, 2);
    dsa::TreeNode* node4 = dsa::BST::insert(root, 4);
    dsa::TreeNode* node7 = dsa::BST::insert(root, 7);
    dsa::TreeNode* node9 = dsa::BST::insert(root, 9);
} // namespace BST
} // namespace dsa_test

GTEST_TEST(Others_BST, is_bst)
{
    EXPECT_TRUE(dsa::BST::is_bst(dsa_test::BST::root));

    dsa::TreeNode* root = new dsa::TreeNode { 5 };
    dsa::Tree::insert_left(root, 3);
    dsa::Tree::insert_right(root, 2);

    EXPECT_FALSE(dsa::BST::is_bst(root));

    dsa::Tree::clear_tree(root);
}

GTEST_TEST(Others_BST, find)
{
    EXPECT_EQ(dsa_test::BST::node7->val, 7);
    EXPECT_EQ(dsa::BST::find(dsa_test::BST::root, 7), dsa_test::BST::node7);
    EXPECT_EQ(dsa::BST::find(nullptr, 7), nullptr);
    EXPECT_EQ(dsa::BST::find(dsa_test::BST::root, 10), nullptr);
}

GTEST_TEST(Others_BST, insert)
{
    dsa::TreeNode* root = dsa::BST::insert(nullptr, 7);
    EXPECT_EQ(root->val, 7);
    EXPECT_EQ(dsa::BST::insert(dsa_test::BST::root, 7), nullptr);
    dsa::TreeNode* node1 = dsa::BST::insert(dsa_test::BST::root, 1);
    EXPECT_EQ(node1->val, 1);

    delete root;
}

GTEST_TEST(Others_BST, min)
{
    EXPECT_THROW(dsa::BST::min(nullptr), std::invalid_argument);
    EXPECT_EQ(dsa::BST::min(dsa_test::BST::root), 1);
}

GTEST_TEST(Others_BST, max)
{
    EXPECT_THROW(dsa::BST::max(nullptr), std::invalid_argument);
    EXPECT_EQ(dsa::BST::max(dsa_test::BST::root), 9);
}

GTEST_TEST(Others_BST, successor)
{
    EXPECT_EQ(dsa::BST::successor(dsa_test::BST::root, 10), nullptr);
    EXPECT_EQ(dsa::BST::successor(dsa_test::BST::root, 8), dsa_test::BST::node9);
    EXPECT_EQ(dsa::BST::successor(dsa_test::BST::root, 6), dsa_test::BST::node7);
    EXPECT_EQ(dsa::BST::successor(dsa_test::BST::root, 2), dsa_test::BST::node3);
}

GTEST_TEST(Others_BST, count)
{
    EXPECT_EQ(dsa::BST::count(dsa_test::BST::root), 8);
    EXPECT_EQ(dsa::BST::count(nullptr), 0);
}

GTEST_TEST(Others_BST, height)
{
    EXPECT_EQ(dsa::BST::height(dsa_test::BST::root), 4);
    EXPECT_EQ(dsa::BST::height(nullptr), 0);
}

GTEST_TEST(Others_BST, sort)
{
    const dsa::Vector<int> orders = dsa::BST::sort(dsa_test::BST::root);
    EXPECT_EQ(orders.size(), 8);
    EXPECT_EQ(orders[0], 1);
    EXPECT_EQ(orders[1], 2);
    EXPECT_EQ(orders[2], 3);
    EXPECT_EQ(orders[3], 4);
    EXPECT_EQ(orders[4], 5);
    EXPECT_EQ(orders[5], 7);
    EXPECT_EQ(orders[6], 8);
    EXPECT_EQ(orders[7], 9);
}

GTEST_TEST(Others_BST, delete_val)
{
    EXPECT_EQ(dsa::BST::delete_val(dsa_test::BST::root, 6), dsa_test::BST::root);
    EXPECT_EQ(dsa::BST::delete_val(dsa_test::BST::root, 8), dsa_test::BST::root);
    EXPECT_EQ(dsa::BST::find(dsa_test::BST::root, 8), nullptr);

    EXPECT_EQ(dsa::BST::delete_val(dsa_test::BST::root, 5), dsa_test::BST::root);
    EXPECT_EQ(dsa_test::BST::root->val, 4);
    EXPECT_EQ(dsa::BST::find(dsa_test::BST::root, 5), nullptr);

    EXPECT_EQ(dsa::BST::delete_val(dsa_test::BST::root, 9), dsa_test::BST::root);
    EXPECT_EQ(dsa::BST::find(dsa_test::BST::root, 9), nullptr);

    dsa::Tree::clear_tree(dsa_test::BST::root);
}