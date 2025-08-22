#include "mystl/vector.h"
#include <gtest/gtest.h>
#include <stdexcept>

namespace mystl_test
{
namespace vector
{
    const mystl::vector<int> VEC = { 1, 2, 3, 4, 5 };
    const mystl::vector<int> EMPTY_VECTOR;
} // namespace vector
} // namespace mystl_test

GTEST_TEST(mystl_vector, initialise)
{
    EXPECT_TRUE(mystl_test::vector::EMPTY_VECTOR.empty());
    EXPECT_EQ(mystl_test::vector::EMPTY_VECTOR.capacity(), 0);
}

GTEST_TEST(mystl_vector, initialise_with_size)
{
    const mystl::size_t vecSize = 5;
    mystl::vector<int>  vec(vecSize);

    EXPECT_EQ(vec.size(), vecSize);
    EXPECT_EQ(vec.capacity(), vecSize);

    for (mystl::size_t i = 0; i < vec.size(); ++i)
    {
        EXPECT_EQ(vec[i], 0);
    }
}

GTEST_TEST(mystl_vector, initialise_with_size_and_value)
{
    const mystl::size_t vecSize = 5;
    const int         val     = 3;
    mystl::vector<int>  vec(vecSize, val);

    EXPECT_EQ(vec.size(), vecSize);
    EXPECT_EQ(vec.capacity(), vecSize);

    for (mystl::size_t i = 0; i < vec.size(); ++i)
    {
        EXPECT_EQ(vec[i], val);
    }
}

GTEST_TEST(mystl_vector, initialise_with_list)
{
    const std::initializer_list<int> list = { 1, 2, 3, 4, 5 };
    mystl::vector<int>                 vec  = list;

    EXPECT_EQ(vec.size(), list.size());
    EXPECT_EQ(vec.capacity(), list.size());

    mystl::size_t idx = 0;
    for (const int val : list)
    {
        EXPECT_EQ(vec[idx++], val);
    }
}

GTEST_TEST(mystl_vector, size)
{
    EXPECT_EQ(mystl_test::vector::VEC.size(), 5);
}

GTEST_TEST(mystl_vector, capacity)
{
    EXPECT_EQ(mystl_test::vector::VEC.capacity(), 5);
}

GTEST_TEST(mystl_vector, empty_true)
{
    EXPECT_TRUE(mystl_test::vector::EMPTY_VECTOR.empty());
}

GTEST_TEST(mystl_vector, empty_false)
{
    EXPECT_FALSE(mystl_test::vector::VEC.empty());
}

GTEST_TEST(mystl_vector, subscript_operation_access)
{
    EXPECT_EQ(mystl_test::vector::VEC[0], 1);
    EXPECT_EQ(mystl_test::vector::VEC[1], 2);
    EXPECT_EQ(mystl_test::vector::VEC[2], 3);
    EXPECT_EQ(mystl_test::vector::VEC[3], 4);
    EXPECT_EQ(mystl_test::vector::VEC[4], 5);
}

GTEST_TEST(mystl_vector, subscript_operation_modify)
{
    mystl::vector<int> vec = { 1 };
    EXPECT_EQ(vec[0], 1);
    vec[0] = 3;
    EXPECT_EQ(vec[0], 3);
}

GTEST_TEST(mystl_vector, at_access)
{
    EXPECT_EQ(mystl_test::vector::VEC.at(0), 1);
    EXPECT_EQ(mystl_test::vector::VEC.at(1), 2);
    EXPECT_EQ(mystl_test::vector::VEC.at(2), 3);
    EXPECT_EQ(mystl_test::vector::VEC.at(3), 4);
    EXPECT_EQ(mystl_test::vector::VEC.at(4), 5);
}

GTEST_TEST(mystl_vector, at_access_out_of_range)
{
    EXPECT_THROW(mystl_test::vector::VEC.at(6), std::out_of_range);
}

GTEST_TEST(mystl_vector, at_modify)
{
    mystl::vector<int> vec = { 1 };
    EXPECT_EQ(vec.at(0), 1);
    vec.at(0) = 3;
    EXPECT_EQ(vec.at(0), 3);
}

GTEST_TEST(mystl_vector, at_modify_out_of_range)
{
    mystl::vector<int> vec = { 1 };

    EXPECT_THROW(vec.at(3) = 3, std::out_of_range);
}

GTEST_TEST(mystl_vector, front)
{
    EXPECT_EQ(mystl_test::vector::VEC.front(), 1);
}

GTEST_TEST(mystl_vector, back)
{
    EXPECT_EQ(mystl_test::vector::VEC.back(), 5);
}

GTEST_TEST(mystl_vector, push_back)
{
    mystl::vector<int> vec = { 1, 2, 3 };

    vec.push_back(4);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec.capacity(), 6);
    EXPECT_EQ(vec[3], 4);

    vec.push_back(5);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.capacity(), 6);
    EXPECT_EQ(vec[4], 5);
}

GTEST_TEST(mystl_vector, pop_back)
{
    mystl::vector<int> vec { 1, 2, 3 };

    vec.pop_back();
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
}

GTEST_TEST(mystl_vector, insert_with_resizing_capacity)
{
    mystl::vector<int> vec = { 1, 2, 3 };

    vec.insert(mystl::next(vec.begin(), 2), 4);
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec.capacity(), 6);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 4);
    EXPECT_EQ(vec[3], 3);
}

GTEST_TEST(mystl_vector, insert_without_resizing_capacity)
{
    mystl::vector<int> vec { 1, 2, 3 };
    vec.push_back(4);

    const mystl::size_t capBeforeInsert = vec.capacity();

    vec.insert(vec.begin(), 5);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec.capacity(), capBeforeInsert);
    EXPECT_EQ(vec[0], 5);
    EXPECT_EQ(vec[1], 1);
    EXPECT_EQ(vec[2], 2);
    EXPECT_EQ(vec[3], 3);
    EXPECT_EQ(vec[4], 4);
}

GTEST_TEST(mystl_vector, insert_multiple_values)
{
    mystl::vector<int> vec { 1, 2, 3 };
    vec.insert(vec.begin() + 1, 3, 99);

    EXPECT_EQ(vec.size(), 6);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 99);
    EXPECT_EQ(vec[2], 99);
    EXPECT_EQ(vec[3], 99);
    EXPECT_EQ(vec[4], 2);
    EXPECT_EQ(vec[5], 3);
}

GTEST_TEST(mystl_vector, insert_range)
{
    mystl::vector<int> vec { 1, 2, 3 };
    mystl::vector<int> input = { 7, 8, 9 };

    vec.insert(vec.begin() + 2, input.begin(), input.end());

    EXPECT_EQ(vec.size(), 6);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 7);
    EXPECT_EQ(vec[3], 8);
    EXPECT_EQ(vec[4], 9);
    EXPECT_EQ(vec[5], 3);
}

GTEST_TEST(mystl_vector, erase)
{
    mystl::vector<int> vec { 1, 2, 3 };

    vec.erase(vec.begin());

    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 2);
    EXPECT_EQ(vec[1], 3);
}

GTEST_TEST(mystl_vector, erase_range)
{
    mystl::vector<int> vec { 10, 20, 30, 40, 50 };

    mystl::vector<int>::iterator first = vec.begin() + 1;
    mystl::vector<int>::iterator last  = vec.begin() + 4;
    mystl::vector<int>::iterator it    = vec.erase(first, last);

    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec[1], 50);
    EXPECT_EQ(*it, 50);
}

GTEST_TEST(mystl_vector, erase_empty_range)
{
    mystl::vector<int> vec { 1, 2, 3 };
    mystl::vector<int>::iterator it = vec.erase(vec.begin() + 1, vec.begin() + 1);

    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(*it, 2); 
}

GTEST_TEST(mystl_vector, reserve)
{
    mystl::vector<int> vec { 1, 2, 3, 2, 5, 2 };
    EXPECT_EQ(vec.capacity(), 6);
    vec.reserve(3);
    EXPECT_EQ(vec.capacity(), 6);
    vec.reserve(12);
    EXPECT_EQ(vec.capacity(), 12);
}
