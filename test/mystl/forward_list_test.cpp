#include "mystl/algorithm.h"
#include "mystl/forward_list.h"
#include "mystl/iterator.h"
#include "mystl/vector.h"
#include <gtest/gtest.h>

namespace mystl_test
{
namespace forward_list
{
    const mystl::forward_list<int> EMPTY_LIST;
    const mystl::forward_list<int> FORWARD_LIST = { 1, 2, 3, 4, 5 };
} // namespace forward_list
} // namespace mystl_test

GTEST_TEST(mystl_forward_list, initialise_with_size_and_value)
{
    const mystl::forward_list<int> ll(5, 2);
    EXPECT_TRUE(mystl::equal(ll.begin(),
                             ll.end(),
                             mystl::vector<int> { 2, 2, 2, 2, 2 }.begin()));
}

GTEST_TEST(mystl_forward_list, initialise_with_list)
{
    EXPECT_TRUE(mystl::equal(mystl_test::forward_list::FORWARD_LIST.begin(),
                             mystl_test::forward_list::FORWARD_LIST.end(),
                             mystl::vector<int> { 1, 2, 3, 4, 5 }.begin()));
}

GTEST_TEST(mystl_forward_list, empty_true)
{
    EXPECT_TRUE(mystl_test::forward_list::EMPTY_LIST.empty());
}

GTEST_TEST(mystl_forward_list, empty_false)
{
    EXPECT_FALSE(mystl_test::forward_list::FORWARD_LIST.empty());
}

GTEST_TEST(mystl_forward_list, push_front)
{
    mystl::forward_list<int> fl = { 1, 2, 3 };
    fl.push_front(5);
    EXPECT_EQ(fl.front(), 5);
}

GTEST_TEST(mystl_forward_list, push_front_empty)
{
    mystl::forward_list<int> fl;
    fl.push_front(5);
    EXPECT_EQ(fl.front(), 5);
}

GTEST_TEST(mystl_forward_list, pop_front)
{
    mystl::forward_list<int> fl = { 1, 2, 3 };
    EXPECT_EQ(fl.pop_front(), 1);
    EXPECT_EQ(fl.front(), 2);
}

GTEST_TEST(mystl_forward_list, front)
{
    EXPECT_EQ(mystl_test::forward_list::FORWARD_LIST.front(), 1);
}

GTEST_TEST(mystl_forward_list, insert_front)
{
    mystl::forward_list<int> fl = { 1, 2, 3 };
    EXPECT_EQ(*fl.insert_after(fl.before_begin(), 5), 5);
    EXPECT_EQ(fl.front(), 5);
}

GTEST_TEST(mystl_forward_list, insert_after)
{
    mystl::forward_list<int> fl = { 1, 2, 3 };

    EXPECT_EQ(*fl.insert_after(mystl::next(fl.begin()), 5), 5);
    EXPECT_TRUE(mystl::equal(fl.begin(), fl.end(), mystl::vector<int> { 1, 2, 5, 3 }.begin()));
}

GTEST_TEST(mystl_forward_list, erase_front)
{
    mystl::forward_list<int> fl = { 1, 2, 3, 4 };
    EXPECT_EQ(*fl.erase_after(fl.before_begin()), 2);
    EXPECT_EQ(fl.front(), 2);
}

GTEST_TEST(mystl_forward_list, erase)
{
    mystl::forward_list<int> fl = { 1, 2, 3, 4 };
    EXPECT_EQ(*fl.erase_after(mystl::next(fl.before_begin(), 2)), 4);
    EXPECT_TRUE(mystl::equal(fl.begin(), fl.end(), mystl::vector<int> { 1, 2, 4 }.begin()));
}

GTEST_TEST(mystl_forward_list, remove)
{
    mystl::forward_list<int> fl = { 2, 1, 2, 3, 4, 2 };
    EXPECT_EQ(fl.remove(2), 3);
    EXPECT_TRUE(mystl::equal(fl.begin(), fl.end(), mystl::vector<int> { 1, 3, 4 }.begin()));
}

GTEST_TEST(mystl_forward_list, remove_all_same)
{
    mystl::forward_list<int> fl = { 2, 2, 2, 2, 2, 2 };
    EXPECT_EQ(fl.remove(2), 6);
    EXPECT_TRUE(fl.empty());
}

GTEST_TEST(mystl_forward_list, reverse)
{
    mystl::forward_list<int> fl = { 2, 1, 2, 3, 4, 5 };
    fl.reverse();
    EXPECT_TRUE(mystl::equal(fl.begin(),
                             fl.end(),
                             mystl::vector<int> { 5, 4, 3, 2, 1, 2 }.begin()));
}

GTEST_TEST(mystl_forward_list, reverse_empty)
{
    mystl::forward_list<int> fl;
    fl.reverse();
    EXPECT_TRUE(fl.empty());
}

GTEST_TEST(mystl_forward_list, reverse_one)
{
    mystl::forward_list<int> fl = { 2 };
    fl.reverse();
    EXPECT_EQ(fl.front(), 2);
}