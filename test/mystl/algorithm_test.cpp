#include "mystl/algorithm.h"
#include "mystl/iterator.h"
#include "mystl/vector.h"

#include "gtest/gtest.h"

namespace mystl_test
{
namespace binary_search
{
    const mystl::vector<int> VEC = { 1, 1, 2, 3, 3, 3, 4, 4, 5, 7, 7 };
}
} // namespace mystl_test

GTEST_TEST(mystl_algorithm, lower_bound_one)
{
    EXPECT_EQ(mystl::lower_bound(mystl_test::binary_search::VEC.begin(), mystl_test::binary_search::VEC.end(), 2), mystl::next(mystl_test::binary_search::VEC.begin(), 2));
    EXPECT_EQ(mystl::lower_bound(mystl_test::binary_search::VEC.begin(), mystl_test::binary_search::VEC.end(), 5), mystl::next(mystl_test::binary_search::VEC.begin(), 8));
}

GTEST_TEST(mystl_algorithm, lower_bound_multiple)
{
    EXPECT_EQ(mystl::lower_bound(mystl_test::binary_search::VEC.begin(), mystl_test::binary_search::VEC.end(), 1), mystl_test::binary_search::VEC.begin());
    EXPECT_EQ(mystl::lower_bound(mystl_test::binary_search::VEC.begin(), mystl_test::binary_search::VEC.end(), 3), mystl::next(mystl_test::binary_search::VEC.begin(), 3));
    EXPECT_EQ(mystl::lower_bound(mystl_test::binary_search::VEC.begin(), mystl_test::binary_search::VEC.end(), 4), mystl::next(mystl_test::binary_search::VEC.begin(), 6));
    EXPECT_EQ(mystl::lower_bound(mystl_test::binary_search::VEC.begin(), mystl_test::binary_search::VEC.end(), 7), mystl::next(mystl_test::binary_search::VEC.begin(), 9));
}

GTEST_TEST(mystl_algorithm, lower_bound_not_found)
{
    EXPECT_EQ(mystl::lower_bound(mystl_test::binary_search::VEC.begin(), mystl_test::binary_search::VEC.end(), 0), mystl_test::binary_search::VEC.begin());
    EXPECT_EQ(mystl::lower_bound(mystl_test::binary_search::VEC.begin(), mystl_test::binary_search::VEC.end(), 6), mystl::next(mystl_test::binary_search::VEC.begin(), 9));
    EXPECT_EQ(mystl::lower_bound(mystl_test::binary_search::VEC.begin(), mystl_test::binary_search::VEC.end(), 9), mystl_test::binary_search::VEC.end());
}

GTEST_TEST(mystl_algorithm, upper_bound)
{
    EXPECT_EQ(mystl::upper_bound(mystl_test::binary_search::VEC.begin(), mystl_test::binary_search::VEC.end(), 1), mystl::next(mystl_test::binary_search::VEC.begin(), 2));
    EXPECT_EQ(mystl::upper_bound(mystl_test::binary_search::VEC.begin(), mystl_test::binary_search::VEC.end(), 3), mystl::next(mystl_test::binary_search::VEC.begin(), 6));
    EXPECT_EQ(mystl::upper_bound(mystl_test::binary_search::VEC.begin(), mystl_test::binary_search::VEC.end(), 6), mystl::next(mystl_test::binary_search::VEC.begin(), 9));
}

GTEST_TEST(mystl_algorithm, upper_bound_larger_than_last)
{
    EXPECT_EQ(mystl::upper_bound(mystl_test::binary_search::VEC.begin(), mystl_test::binary_search::VEC.end(), 9), mystl_test::binary_search::VEC.end());
}

GTEST_TEST(mystl_algorithm, upper_bound_smaller_than_first)
{
    EXPECT_EQ(mystl::upper_bound(mystl_test::binary_search::VEC.begin(), mystl_test::binary_search::VEC.end(), 0), mystl_test::binary_search::VEC.begin());
}

GTEST_TEST(mystl_algorithm, is_heap)
{
    mystl::vector<int> vec { 3, 2, 1, 5, 4, 8, 10, 7, 9, 6, 2, 4, 3, 8, 7, 7, 4 };
    EXPECT_FALSE(mystl::is_heap(vec.begin(), vec.end(), mystl::less<int>()));
    mystl::make_heap(vec.begin(), vec.end(), mystl::less<int>());
    EXPECT_TRUE(mystl::is_heap(vec.begin(), vec.end(), mystl::less<int>()));
}

GTEST_TEST(mystl_algorithm, is_heap_greater)
{
    mystl::vector<int> vec { 3, 2, 1, 5, 4, 8, 10, 7, 9, 6, 2, 4, 3, 8, 7, 7, 4 };
    EXPECT_FALSE(mystl::is_heap(vec.begin(), vec.end(), mystl::greater<int>()));
    mystl::make_heap(vec.begin(), vec.end(), mystl::greater<int>());
    EXPECT_TRUE(mystl::is_heap(vec.begin(), vec.end(), mystl::greater<int>()));
}

GTEST_TEST(mystl_algorithm, is_heap_until)
{
    mystl::vector<int> vec { 3, 2, 1, 5, 4, 8, 10, 7, 9, 6, 2, 4, 3, 8, 7, 7, 4 };
    EXPECT_EQ(mystl::is_heap_until(vec.begin(), vec.end(), mystl::less<int>()), vec.begin() + 3);
    mystl::make_heap(vec.begin(), vec.end(), mystl::less<int>());
    EXPECT_EQ(mystl::is_heap_until(vec.begin(), vec.end(), mystl::less<int>()), vec.end());
}

GTEST_TEST(mystl_algorithm, sort_heap)
{
    mystl::vector<int> vec { 3, 2, 1, 5, 4, 8, 10, 7, 9, 6, 2, 4, 3, 8, 7, 7, 4 };
    mystl::make_heap(vec.begin(), vec.end(), mystl::less<int>());
    mystl::vector<int> res = { 1, 2, 2, 3, 3, 4, 4, 4, 5, 6, 7, 7, 7, 8, 8, 9, 10 };
    mystl::sort_heap(vec.begin(), vec.end(), mystl::less<int>());
    EXPECT_TRUE(mystl::equal(vec.begin(), vec.end(), res.begin()));
    EXPECT_EQ(res.size(), res.size());
}

GTEST_TEST(mystl_algorithm, sort_heap_greater)
{
    mystl::vector<int> vec { 3, 2, 1, 5, 4, 8, 10, 7, 9, 6, 2, 4, 3, 8, 7, 7, 4 };
    mystl::make_heap(vec.begin(), vec.end(), mystl::greater<int>());
    mystl::vector<int> res = { 10, 9, 8, 8, 7, 7, 7, 6, 5, 4, 4, 4, 3, 3, 2, 2, 1 };
    mystl::sort_heap(vec.begin(), vec.end(), mystl::greater<int>());
    EXPECT_TRUE(mystl::equal(vec.begin(), vec.end(), res.begin()));
    EXPECT_EQ(res.size(), res.size());
}