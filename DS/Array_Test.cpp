#include "gtest/gtest.h"

#include "Array.h"

namespace dsa_test
{
namespace Array
{
    const dsa::Array<int, 0> EMPTY_ARRAY;
    const dsa::Array<int, 4> ARRAY4 { 1, 2, 3, 4 };
} // namespace Array
} // namespace dsa_test

GTEST_TEST(DS_Array, initialise_empty)
{
    dsa::Array<int, 0> arr;
    EXPECT_TRUE(arr.empty());
    EXPECT_EQ(arr.size(), 0);
}

GTEST_TEST(DS_Array, initialise_with_list_out_of_range)
{
    EXPECT_THROW(
        static_cast<void>(dsa::Array<int, 5> { 1, 2, 3, 4, 5, 6 }),
        std::overflow_error);
}

GTEST_TEST(DS_Array, initialise_with_smaller_list)
{
    dsa::Array<int, 5> arr { 1, 2, 3 };
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 0);
    EXPECT_EQ(arr[4], 0);
}

GTEST_TEST(DS_Array, initialise)
{
    dsa::Array<int, 4> arr { 1, 2, 3, 4 };
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);
}

GTEST_TEST(DS_Array, empty_true)
{
    EXPECT_TRUE(dsa_test::Array::EMPTY_ARRAY.empty());
}

GTEST_TEST(DS_Array, empty_false)
{
    EXPECT_FALSE(dsa_test::Array::ARRAY4.empty());
}

GTEST_TEST(DS_Array, size)
{
    EXPECT_EQ(dsa_test::Array::EMPTY_ARRAY.size(), 0);
    EXPECT_EQ(dsa_test::Array::ARRAY4.size(), 4);
}

GTEST_TEST(DS_Array, fill)
{
    dsa::Array<int, 64> arr;
    arr.fill(2);
    for (const int val : arr)
    {
        EXPECT_EQ(val, 2);
    }
}