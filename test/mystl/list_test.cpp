#include "mystl/algorithm.h"
#include "mystl/iterator.h"
#include "mystl/list.h"
#include "mystl/vector.h"
#include <gtest/gtest.h>

namespace mystl_test
{
namespace list
{
    const mystl::list<int> EMPTY_LIST;
    const mystl::list<int> LINKED_LIST = { 1, 2, 3, 4, 5 };
} // namespace list
} // namespace mystl_test

GTEST_TEST(mystl_list, initialise_with_size_and_value)
{
    const mystl::list<int> ll(5, 2);
    EXPECT_EQ(ll.size(), 5);
    EXPECT_TRUE(mystl::equal(ll.begin(),
                           ll.end(),
                           mystl::vector<int> { 2, 2, 2, 2, 2 }.begin()));
}

GTEST_TEST(mystl_list, initialise_with_list)
{
    EXPECT_EQ(mystl_test::list::LINKED_LIST.size(), 5);
    EXPECT_TRUE(mystl::equal(mystl_test::list::LINKED_LIST.begin(),
                           mystl_test::list::LINKED_LIST.end(),
                           mystl::vector<int> { 1, 2, 3, 4, 5 }.begin()));
}

GTEST_TEST(mystl_list, size)
{
    EXPECT_EQ(mystl_test::list::LINKED_LIST.size(), 5);
}

GTEST_TEST(mystl_list, empty_true)
{
    EXPECT_TRUE(mystl_test::list::EMPTY_LIST.empty());
}

GTEST_TEST(mystl_list, empty_false)
{
    EXPECT_FALSE(mystl_test::list::LINKED_LIST.empty());
}

GTEST_TEST(mystl_list, push_front)
{
    mystl::list<int> ll = { 1, 2, 3 };

    ll.push_front(5);
    EXPECT_EQ(ll.front(), 5);
    EXPECT_EQ(ll.size(), 4);
}

GTEST_TEST(mystl_list, push_front_empty)
{
    mystl::list<int> ll;
    ll.push_front(5);
    EXPECT_EQ(ll.front(), 5);
    EXPECT_EQ(ll.back(), 5);
    EXPECT_EQ(ll.size(), 1);
}

GTEST_TEST(mystl_list, pop_front)
{
    mystl::list<int> ll = { 1, 2, 3 };
    EXPECT_EQ(ll.pop_front(), 1);
    EXPECT_EQ(ll.front(), 2);
    EXPECT_EQ(ll.size(), 2);
}

GTEST_TEST(mystl_list, push_back)
{
    mystl::list<int> ll = { 1, 2, 3 };
    ll.push_back(5);
    EXPECT_EQ(ll.back(), 5);
    EXPECT_EQ(ll.size(), 4);
}

GTEST_TEST(mystl_list, push_back_empty)
{
    mystl::list<int> ll;
    ll.push_back(5);
    EXPECT_EQ(ll.front(), 5);
    EXPECT_EQ(ll.back(), 5);
    EXPECT_EQ(ll.size(), 1);
}

GTEST_TEST(mystl_list, pop_back)
{
    mystl::list<int> ll = { 1, 2, 3 };
    EXPECT_EQ(ll.pop_back(), 3);
    EXPECT_EQ(ll.back(), 2);
    EXPECT_EQ(ll.size(), 2);
}

GTEST_TEST(mystl_list, front)
{
    EXPECT_EQ(mystl_test::list::LINKED_LIST.front(), 1);
}

GTEST_TEST(mystl_list, back)
{
    EXPECT_EQ(mystl_test::list::LINKED_LIST.back(), 5);
}

GTEST_TEST(mystl_list, insert_back)
{
    mystl::list<int> ll = { 1, 2, 3 };
    EXPECT_EQ(*ll.insert(ll.end(), 5), 5);
    EXPECT_EQ(ll.size(), 4);
    EXPECT_EQ(ll.back(), 5);
}

GTEST_TEST(mystl_list, insert_front)
{
    mystl::list<int> ll = { 1, 2, 3 };
    EXPECT_EQ(*ll.insert(ll.begin(), 5), 5);
    EXPECT_EQ(ll.size(), 4);
    EXPECT_EQ(ll.front(), 5);
}

GTEST_TEST(mystl_list, insert)
{
    mystl::list<int> ll = { 1, 2, 3 };
    EXPECT_EQ(*ll.insert(mystl::next(ll.begin(), 2), 5), 5);
    EXPECT_EQ(ll.size(), 4);
    EXPECT_TRUE(mystl::equal(ll.begin(), ll.end(), mystl::vector<int> { 1, 2,5, 3 }.begin()));
}

GTEST_TEST(mystl_list, erase_back)
{
    mystl::list<int> ll = { 1, 2, 3, 4 };
    EXPECT_EQ(ll.erase(mystl::next(ll.begin(), ll.size() - 1)), ll.end());
    EXPECT_EQ(ll.size(), 3);
    EXPECT_EQ(ll.back(), 3);
}

GTEST_TEST(mystl_list, erase_front)
{
    mystl::list<int> ll = { 1, 2, 3, 4 };
    EXPECT_EQ(*ll.erase(ll.begin()), 2);
    EXPECT_EQ(ll.size(), 3);
    EXPECT_EQ(ll.front(), 2);
}

GTEST_TEST(mystl_list, erase)
{
    mystl::list<int> ll = { 1, 2, 3, 4 };
    EXPECT_EQ(*ll.erase(mystl::next(ll.begin(), 2)), 4);
    EXPECT_TRUE(mystl::equal(ll.begin(), ll.end(), mystl::vector<int>{1, 2, 4}.begin()));
    EXPECT_EQ(ll.size(), 3);
}

GTEST_TEST(mystl_list, remove)
{
    mystl::list<int> ll = { 2, 1, 2, 3, 4, 2 };
    EXPECT_EQ(ll.remove(2), 3);
    EXPECT_EQ(ll.size(), 3);
    EXPECT_TRUE(mystl::equal(ll.begin(), ll.end(), mystl::vector<int> { 1, 3, 4 }.begin()));
}

GTEST_TEST(mystl_list, remove_all_same)
{
    mystl::list<int> ll = { 2, 2, 2, 2, 2, 2 };
    EXPECT_EQ(ll.remove(2), 6);
    EXPECT_TRUE(ll.empty());
}

GTEST_TEST(mystl_list, reverse)
{
    mystl::list<int> ll = { 2, 1, 2, 3, 4, 5 };
    ll.reverse();
    EXPECT_TRUE(mystl::equal(ll.begin(),
                           ll.end(),
                           mystl::vector<int> { 5, 4, 3, 2, 1, 2 }.begin()));
}

GTEST_TEST(mystl_list, reverse_empty)
{
    mystl::list<int> ll;
    ll.reverse();
    EXPECT_TRUE(ll.empty());
}

GTEST_TEST(mystl_list, reverse_one)
{
    mystl::list<int> ll = { 2 };
    ll.reverse();
    EXPECT_EQ(ll.back(), 2);
    EXPECT_EQ(ll.front(), 2);
}
