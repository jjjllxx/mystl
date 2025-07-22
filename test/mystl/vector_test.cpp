#include "mystl/vector.h"
#include <cstddef>
#include <gtest/gtest.h>
#include <stdexcept>

namespace mystl_test
{
namespace vector
{
    const mystl_test::vector<int> VEC = { 1, 2, 3, 4, 5 };
} // namespace vector

GTEST_TEST(DS_Vector, initialise)
{
    mystl_test::vector<int> vec;

    EXPECT_TRUE(vec.empty());
    EXPECT_EQ(vec.capacity(), mystl_test::VECTOR_INITIAL_CAPACITY);
}

GTEST_TEST(DS_Vector, initialise_with_size)
{
    const std::size_t vecSize = 5;
    mystl_test::vector<int> vec(vecSize);

    EXPECT_EQ(vec.size(), vecSize);
    EXPECT_EQ(vec.capacity(), vecSize);

    for (std::size_t i = 0; i < vec.size(); ++i)
    {
        EXPECT_EQ(vec[i], 0);
    }
}

GTEST_TEST(DS_Vector, initialise_with_size_and_value)
{
    const std::size_t vecSize = 5;
    const int         val     = 3;
    mystl_test::vector<int> vec(vecSize, val);

    EXPECT_EQ(vec.size(), vecSize);
    EXPECT_EQ(vec.capacity(), vecSize);

    for (std::size_t i = 0; i < vec.size(); ++i)
    {
        EXPECT_EQ(vec[i], val);
    }
}

GTEST_TEST(DS_Vector, initialise_with_list)
{
    const std::initializer_list<int> list = { 1, 2, 3, 4, 5 };
    mystl_test::vector<int>          vec  = list;

    EXPECT_EQ(vec.size(), list.size());
    EXPECT_EQ(vec.capacity(), list.size());

    std::size_t idx = 0;
    for (const int val : list)
    {
        EXPECT_EQ(vec[idx++], val);
    }
}

GTEST_TEST(DS_Vector, size)
{
    EXPECT_EQ(mystl_test::vector::VEC.size(), 5);
}

GTEST_TEST(DS_Vector, capacity)
{
    EXPECT_EQ(mystl_test::vector::VEC.capacity(), 5);
}

GTEST_TEST(DS_Vector, empty_true)
{
    const mystl_test::vector<int> emptyVector;
    EXPECT_TRUE(emptyVector.empty());
}

GTEST_TEST(DS_Vector, empty_false)
{
    EXPECT_FALSE(mystl_test::vector::VEC.empty());
}

GTEST_TEST(DS_Vector, subscript_operation_access)
{
    EXPECT_EQ(mystl_test::vector::VEC[0], 1);
    EXPECT_EQ(mystl_test::vector::VEC[1], 2);
    EXPECT_EQ(mystl_test::vector::VEC[2], 3);
    EXPECT_EQ(mystl_test::vector::VEC[3], 4);
    EXPECT_EQ(mystl_test::vector::VEC[4], 5);
}

GTEST_TEST(DS_Vector, subscript_operation_modify)
{
    mystl_test::vector<int> vec = { 1 };
    EXPECT_EQ(vec[0], 1);
    vec[0] = 3;
    EXPECT_EQ(vec[0], 3);
}

GTEST_TEST(DS_Vector, at_access)
{
    EXPECT_EQ(mystl_test::vector::VEC.at(0), 1);
    EXPECT_EQ(mystl_test::vector::VEC.at(1), 2);
    EXPECT_EQ(mystl_test::vector::VEC.at(2), 3);
    EXPECT_EQ(mystl_test::vector::VEC.at(3), 4);
    EXPECT_EQ(mystl_test::vector::VEC.at(4), 5);
}

GTEST_TEST(DS_Vector, at_access_out_of_range)
{
    EXPECT_THROW(mystl_test::vector::VEC.at(6), std::out_of_range);
}

GTEST_TEST(DS_Vector, at_modify)
{
    mystl_test::vector<int> vec = { 1 };
    EXPECT_EQ(vec.at(0), 1);
    vec.at(0) = 3;
    EXPECT_EQ(vec.at(0), 3);
}

GTEST_TEST(DS_Vector, at_modify_out_of_range)
{
    mystl_test::vector<int> vec = { 1 };

    EXPECT_THROW(vec.at(3) = 3, std::out_of_range);
}

GTEST_TEST(DS_Vector, find_success)
{
    EXPECT_EQ(mystl_test::vector::VEC.find(3), 2);
}

GTEST_TEST(DS_Vector, find_failure)
{
    EXPECT_EQ(mystl_test::vector::VEC.find(6), -1);
}

GTEST_TEST(DS_Vector, push_with_resizing_capacity)
{
    mystl_test::vector<int> vec = { 1, 2, 3 };

    vec.push(4);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec.capacity(), 6);
    EXPECT_EQ(vec[3], 4);
}

GTEST_TEST(DS_Vector, push_without_resizing_capacity)
{
    mystl_test::vector<int> vec;

    vec.push(5);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec.capacity(), mystl_test::VECTOR_INITIAL_CAPACITY);
    EXPECT_EQ(vec[0], 5);
}

GTEST_TEST(DS_Vector, insert_out_of_range)
{
    mystl_test::vector<int> vec = { 1, 2, 3 };

    EXPECT_THROW(vec.insert(5, 4), std::out_of_range);
}

GTEST_TEST(DS_Vector, insert_with_resizing_capacity)
{
    mystl_test::vector<int> vec = { 1, 2, 3 };

    vec.insert(2, 4);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec.capacity(), 6);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 4);
    EXPECT_EQ(vec[3], 3);
}

GTEST_TEST(DS_Vector, insert_without_resizing_capacity)
{
    mystl_test::vector<int> vec { 1, 2, 3 };
    vec.push(4);

    const std::size_t capBeforeInsert = vec.capacity();

    vec.insert(0, 5);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.capacity(), capBeforeInsert);
    EXPECT_EQ(vec[0], 5);
    EXPECT_EQ(vec[1], 1);
    EXPECT_EQ(vec[2], 2);
    EXPECT_EQ(vec[3], 3);
    EXPECT_EQ(vec[4], 4);
}

GTEST_TEST(DS_Vector, prepend)
{
    mystl_test::vector<int> vec;
    vec.prepend(4);
    EXPECT_EQ(vec[0], 4);
}

GTEST_TEST(DS_Vector, pop_on_empty_vector)
{
    mystl_test::vector<int> vec;
    EXPECT_THROW(vec.pop(), std::out_of_range);
}

GTEST_TEST(DS_Vector, pop_without_resizing_capacity)
{
    mystl_test::vector<int> vec { 1, 2, 3 };

    const std::size_t capBeforePop = vec.capacity();

    EXPECT_EQ(vec.pop(), 3);
    EXPECT_EQ(vec.capacity(), capBeforePop);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
}

GTEST_TEST(DS_Vector, pop_with_resizing_capacity)
{
    mystl_test::vector<int> vec;
    vec.push(1);
    vec.push(2);
    vec.push(3);

    const std::size_t capBeforePop = vec.capacity();

    EXPECT_EQ(vec.pop(), 3);
    EXPECT_EQ(vec.capacity(), capBeforePop >> 1);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
}

GTEST_TEST(DS_Vector, erase_out_of_range)
{
    mystl_test::vector<int> vec = { 1, 2, 3 };

    EXPECT_THROW(vec.erase(5), std::out_of_range);
}

GTEST_TEST(DS_Vector, erase)
{
    mystl_test::vector<int> vec = { 1, 2, 3 };

    vec.erase(0);

    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 2);
    EXPECT_EQ(vec[1], 3);
}

GTEST_TEST(DS_Vector, remove)
{
    mystl_test::vector<int> vec = { 1, 2, 3, 2, 5, 2 };

    vec.remove(2);

    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 3);
    EXPECT_EQ(vec[2], 5);
}
} // namespace mystl_test