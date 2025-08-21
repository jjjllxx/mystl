#include "extensions/binary_search_tree.h"
#include "extensions/tree.h"
#include "mystl/vector.h"

#include "gtest/gtest.h"
#include <stdexcept>

namespace ext_test
{
namespace bst
{
    ext::tree_node* root  = new ext::tree_node { 5 };
    ext::tree_node* node3 = ext::bst::insert(root, 3);
    ext::tree_node* node8 = ext::bst::insert(root, 8);
    ext::tree_node* node2 = ext::bst::insert(root, 2);
    ext::tree_node* node4 = ext::bst::insert(root, 4);
    ext::tree_node* node7 = ext::bst::insert(root, 7);
    ext::tree_node* node9 = ext::bst::insert(root, 9);
} // namespace bst
} // namespace ext_test

GTEST_TEST(ext_bst, is_bst)
{
    EXPECT_TRUE(ext::bst::is_bst(ext_test::bst::root));

    ext::tree_node* root = new ext::tree_node { 5 };
    ext::tree::insert_left(root, 3);
    ext::tree::insert_right(root, 2);
    EXPECT_FALSE(ext::bst::is_bst(root));

    ext::tree::clear_tree(root);
}

GTEST_TEST(ext_bst, find)
{
    EXPECT_EQ(ext::bst::find(ext_test::bst::root, 7)->val, 7);
    EXPECT_EQ(ext::bst::find(nullptr, 7), nullptr);
    EXPECT_EQ(ext::bst::find(ext_test::bst::root, 10), nullptr);
}

GTEST_TEST(ext_bst, insert)
{
    ext::tree_node* tmp = ext::bst::insert(nullptr, 7);
    EXPECT_EQ(tmp->val, 7);
    delete tmp;

    EXPECT_EQ(ext::bst::count(ext_test::bst::root), 7);
    ext::bst::insert(ext_test::bst::root, 1);
    EXPECT_EQ(ext::bst::count(ext_test::bst::root), 8);
}

GTEST_TEST(ext_bst, min)
{
    EXPECT_THROW(ext::bst::min(nullptr), std::invalid_argument);
    EXPECT_EQ(ext::bst::min(ext_test::bst::root), 1);
}

GTEST_TEST(ext_bst, max)
{
    EXPECT_THROW(ext::bst::max(nullptr), std::invalid_argument);
    EXPECT_EQ(ext::bst::max(ext_test::bst::root), 9);
}

GTEST_TEST(ext_bst, height)
{
    EXPECT_EQ(ext::bst::height(ext_test::bst::root), 3);
    EXPECT_EQ(ext::bst::height(nullptr), -1);
}

GTEST_TEST(ext_bst, successor)
{
    EXPECT_EQ(ext::bst::successor(ext_test::bst::root, 10), nullptr);
    EXPECT_EQ(ext::bst::successor(ext_test::bst::root, 8)->val, 9);
    EXPECT_EQ(ext::bst::successor(ext_test::bst::root, 6)->val, 7);
    EXPECT_EQ(ext::bst::successor(ext_test::bst::root, 2)->val, 3);
}

GTEST_TEST(ext_bst, count)
{
    EXPECT_EQ(ext::bst::count(ext_test::bst::root), 8);
    EXPECT_EQ(ext::bst::count(nullptr), 0);
}

GTEST_TEST(ext_bst, sort)
{
    const mystl::vector<int> orders = ext::bst::sort(ext_test::bst::root);
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

GTEST_TEST(ext_bst, delete_)
{
    EXPECT_EQ(ext::bst::delete_(ext_test::bst::root, 6), ext_test::bst::root);
    EXPECT_EQ(ext::bst::delete_(ext_test::bst::root, 8), ext_test::bst::root);
    EXPECT_EQ(ext::bst::find(ext_test::bst::root, 8), nullptr);
    EXPECT_TRUE(ext::bst::is_bst(ext_test::bst::root));

    EXPECT_EQ(ext::bst::delete_(ext_test::bst::root, 5), ext_test::bst::root);
    EXPECT_EQ(ext_test::bst::root->val, 7);
    EXPECT_EQ(ext::bst::find(ext_test::bst::root, 5), nullptr);
    EXPECT_TRUE(ext::bst::is_bst(ext_test::bst::root));

    EXPECT_EQ(ext::bst::delete_(ext_test::bst::root, 9), ext_test::bst::root);
    EXPECT_EQ(ext::bst::find(ext_test::bst::root, 9), nullptr);
    EXPECT_TRUE(ext::bst::is_bst(ext_test::bst::root));

    ext::tree::clear_tree(ext_test::bst::root);
}