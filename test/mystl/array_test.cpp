#include "gtest/gtest.h"

#include "mystl/array.h"

namespace mystl_test
{
namespace array
{
    const mystl::array<int, 0> EMPTY_ARRAY;
    const mystl::array<int, 4> ARRAY4 { 1, 2, 3, 4 };
} // namespace array
} // namespace mystl_test

GTEST_TEST(DS_Array, initialise_empty)
{
    mystl::array<int, 0> arr;
    EXPECT_TRUE(arr.empty());
    EXPECT_EQ(arr.size(), 0);
}

GTEST_TEST(DS_Array, initialise_with_list_out_of_range)
{
    EXPECT_THROW(
        static_cast<void>(mystl::array<int, 5> { 1, 2, 3, 4, 5, 6 }),
        std::overflow_error);
}

GTEST_TEST(DS_Array, initialise_with_smaller_list)
{
    mystl::array<int, 5> arr { 1, 2, 3 };
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 0);
    EXPECT_EQ(arr[4], 0);
}

GTEST_TEST(DS_Array, initialise)
{
    mystl::array<int, 4> arr { 1, 2, 3, 4 };
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);
}

GTEST_TEST(DS_Array, empty_true)
{
    EXPECT_TRUE(mystl_test::array::EMPTY_ARRAY.empty());
}

GTEST_TEST(DS_Array, empty_false)
{
    EXPECT_FALSE(mystl_test::array::ARRAY4.empty());
}

GTEST_TEST(DS_Array, size)
{
    EXPECT_EQ(mystl_test::array::EMPTY_ARRAY.size(), 0);
    EXPECT_EQ(mystl_test::array::ARRAY4.size(), 4);
}

GTEST_TEST(DS_Array, fill)
{
    mystl::array<int, 64> arr;
    arr.fill(2);
    for (const int val : arr)
    {
        EXPECT_EQ(val, 2);
    }
}