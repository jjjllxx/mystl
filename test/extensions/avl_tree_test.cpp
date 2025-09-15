#include "extensions/avl_tree.h"
#include "mystl/vector.h"

#include "gtest/gtest.h"

namespace ext_test
{
namespace avl
{
    const mystl::vector<int> VALUES = { 30, 20, 40, 10, 25, 35, 50, 5, 15, 27, 33, 37, 45, 55, 60, 42, 43, 44 };
} // namespace avl
} // namespace ext_test

GTEST_TEST(ext_avl, is_val_tree)
{
    ext::avl_node* root = nullptr;
    for (const int v : ext_test::avl::VALUES)
    {
        root = ext::avl::insert(root, v);
    }

    EXPECT_TRUE(ext::avl::is_avl_tree(root));

    ext::avl::clear(root);
}

GTEST_TEST(ext_avl, find)
{
    ext::avl_node* root = nullptr;
    for (const int v : ext_test::avl::VALUES)
    {
        root = ext::avl::insert(root, v);
    }

    EXPECT_TRUE(ext::avl::find(root, 33));
    EXPECT_FALSE(ext::avl::find(root, 26));

    ext::avl::clear(root);
}

GTEST_TEST(ext_avl, delete_)
{
    ext::avl_node* root = nullptr;
    for (const int v : ext_test::avl::VALUES)
    {
        root = ext::avl::insert(root, v);
    }

    EXPECT_EQ(root->val, 30);

    root = ext::avl::delete_(root, 30);
    EXPECT_EQ(ext::avl::find(root, 30), nullptr);
    EXPECT_EQ(root->val, 33);
    EXPECT_TRUE(ext::avl::is_avl_tree(root));

    ext::avl::clear(root);
}