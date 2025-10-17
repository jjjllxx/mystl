#include "extensions/sort.h"
#include "mystl/vector.h"
#include "gtest/gtest.h"

namespace ext_test
{
const mystl::vector<int> EMPTY             = {};
const mystl::vector<int> ONE_ELEMENT       = { 42 };
const mystl::vector<int> ALREADY_SORTED    = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
const mystl::vector<int> REVERSE_SORTED    = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
const mystl::vector<int> RANDOM_ORDER      = { 3, 7, 1, 9, 4, 10, 5, 6, 2, 8 };
const mystl::vector<int> ALL_IDENTICAL     = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
const mystl::vector<int> NEARLY_SORTED     = { 1, 2, 3, 5, 4, 6, 7, 8, 9, 10 };
const mystl::vector<int> FEW_UNIQUE        = { 3, 1, 3, 2, 3, 1, 2, 3, 1, 2 };
const mystl::vector<int> SORTED_FEW_UNIQUE = { 1, 1, 1, 2, 2, 2, 3, 3, 3, 3 };
} // namespace ext_test

GTEST_TEST(ext_sort, merge_sort_recursive)
{
    mystl::vector<int> vec = ext_test::EMPTY;
    ext::sort::merge_sort_recursive(vec.begin(), 0, vec.size());
    EXPECT_TRUE(mystl::equal(vec.begin(), vec.end(), ext_test::EMPTY.begin()));

    vec = ext_test::ONE_ELEMENT;
    ext::sort::merge_sort_recursive(vec.begin(), 0, vec.size());
    EXPECT_TRUE(mystl::equal(vec.begin(), vec.end(), ext_test::ONE_ELEMENT.begin()));

    vec = ext_test::ALREADY_SORTED;
    ext::sort::merge_sort_recursive(vec.begin(), 0, vec.size());
    EXPECT_TRUE(mystl::equal(vec.begin(), vec.end(), ext_test::ALREADY_SORTED.begin()));

    vec = ext_test::REVERSE_SORTED;
    ext::sort::merge_sort_recursive(vec.begin(), 0, vec.size());
    EXPECT_TRUE(mystl::equal(vec.begin(), vec.end(), ext_test::ALREADY_SORTED.begin()));

    vec = ext_test::RANDOM_ORDER;
    ext::sort::merge_sort_recursive(vec.begin(), 0, vec.size());
    EXPECT_TRUE(mystl::equal(vec.begin(), vec.end(), ext_test::ALREADY_SORTED.begin()));

    vec = ext_test::ALL_IDENTICAL;
    ext::sort::merge_sort_recursive(vec.begin(), 0, vec.size());
    EXPECT_TRUE(mystl::equal(vec.begin(), vec.end(), ext_test::ALL_IDENTICAL.begin()));

    vec = ext_test::NEARLY_SORTED;
    ext::sort::merge_sort_recursive(vec.begin(), 0, vec.size());
    EXPECT_TRUE(mystl::equal(vec.begin(), vec.end(), ext_test::ALREADY_SORTED.begin()));

    vec = ext_test::FEW_UNIQUE;
    ext::sort::merge_sort_recursive(vec.begin(), 0, vec.size());
    EXPECT_TRUE(mystl::equal(vec.begin(), vec.end(), ext_test::SORTED_FEW_UNIQUE.begin()));
}

GTEST_TEST(ext_sort, merge_sort_iterative)
{
    mystl::vector<int> vec = ext_test::EMPTY;
    ext::sort::merge_sort_iterative(vec.begin(), 0, vec.size());
    EXPECT_TRUE(mystl::equal(vec.begin(), vec.end(), ext_test::EMPTY.begin()));

    vec = ext_test::ONE_ELEMENT;
    ext::sort::merge_sort_iterative(vec.begin(), 0, vec.size());
    EXPECT_TRUE(mystl::equal(vec.begin(), vec.end(), ext_test::ONE_ELEMENT.begin()));

    vec = ext_test::ALREADY_SORTED;
    ext::sort::merge_sort_iterative(vec.begin(), 0, vec.size());
    EXPECT_TRUE(mystl::equal(vec.begin(), vec.end(), ext_test::ALREADY_SORTED.begin()));

    vec = ext_test::REVERSE_SORTED;
    ext::sort::merge_sort_iterative(vec.begin(), 0, vec.size());
    EXPECT_TRUE(mystl::equal(vec.begin(), vec.end(), ext_test::ALREADY_SORTED.begin()));

    vec = ext_test::RANDOM_ORDER;
    ext::sort::merge_sort_iterative(vec.begin(), 0, vec.size());
    EXPECT_TRUE(mystl::equal(vec.begin(), vec.end(), ext_test::ALREADY_SORTED.begin()));

    vec = ext_test::ALL_IDENTICAL;
    ext::sort::merge_sort_iterative(vec.begin(), 0, vec.size());
    EXPECT_TRUE(mystl::equal(vec.begin(), vec.end(), ext_test::ALL_IDENTICAL.begin()));

    vec = ext_test::NEARLY_SORTED;
    ext::sort::merge_sort_iterative(vec.begin(), 0, vec.size());
    EXPECT_TRUE(mystl::equal(vec.begin(), vec.end(), ext_test::ALREADY_SORTED.begin()));

    vec = ext_test::FEW_UNIQUE;
    ext::sort::merge_sort_iterative(vec.begin(), 0, vec.size());
    EXPECT_TRUE(mystl::equal(vec.begin(), vec.end(), ext_test::SORTED_FEW_UNIQUE.begin()));
}