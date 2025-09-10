#include "mystl/algorithm.h"
#include "mystl/deque.h"
#include "mystl/vector.h"
#include "gtest/gtest.h"

#include <stdexcept>

namespace mystl_test
{
namespace deque
{
    const mystl::deque<int> EMPTY_DEQUE;
    const mystl::deque<int> DEQUE1 = { 1, 2, 3, 4, 5 };
} // namespace deque
} // namespace mystl_test

GTEST_TEST(mystl_deque, initialise_empty)
{
    EXPECT_TRUE(mystl_test::deque::EMPTY_DEQUE.empty());
    EXPECT_EQ(mystl_test::deque::EMPTY_DEQUE.begin(), mystl_test::deque::EMPTY_DEQUE.end());
}

GTEST_TEST(mystl_deque, initialise_with_size)
{
    const mystl::deque<int> dq(5);
    EXPECT_EQ(dq.size(), 5);
    EXPECT_TRUE(mystl::equal(dq.begin(), dq.end(), mystl::vector<int>(5).begin()));
}

GTEST_TEST(mystl_deque, initialise_with_size_and_value)
{
    const mystl::deque<int> dq(6, 2);
    EXPECT_EQ(dq.size(), 6);
    EXPECT_TRUE(mystl::equal(dq.begin(), dq.end(), mystl::vector<int>(6, 2).begin()));
}

GTEST_TEST(mystl_deque, initialise_with_list)
{
    EXPECT_EQ(mystl_test::deque::DEQUE1.size(), 5);
    EXPECT_TRUE(mystl::equal(mystl_test::deque::DEQUE1.begin(),
                           mystl_test::deque::DEQUE1.end(),
                           mystl::vector<int> { 1, 2, 3, 4, 5 }.begin()));
}

GTEST_TEST(mystl_deque, initialise_with_iterator)
{
    const mystl::vector<int> vec = { 5, 4, 3, 2, 1 };
    const mystl::deque<int>  dq(vec.begin(), vec.end());
    EXPECT_EQ(dq.size(), 5);
    EXPECT_TRUE(mystl::equal(dq.begin(), dq.end(), vec.begin()));
}

GTEST_TEST(mystl_deque, initialise_copy)
{
    const mystl::deque<int> dq(mystl_test::deque::DEQUE1);
    EXPECT_EQ(dq.size(), mystl_test::deque::DEQUE1.size());
    EXPECT_TRUE(mystl::equal(dq.begin(), dq.end(), mystl_test::deque::DEQUE1.begin()));
}

GTEST_TEST(mystl_deque, front)
{
    EXPECT_EQ(mystl_test::deque::DEQUE1.front(), 1);
}

GTEST_TEST(mystl_deque, back)
{
    EXPECT_EQ(mystl_test::deque::DEQUE1.back(), 5);
}

GTEST_TEST(mystl_deque, size)
{
    EXPECT_EQ(mystl_test::deque::DEQUE1.size(), 5);
    EXPECT_EQ(mystl_test::deque::EMPTY_DEQUE.size(), 0);
}

GTEST_TEST(mystl_deque, empty)
{
    EXPECT_TRUE(mystl_test::deque::EMPTY_DEQUE.empty());
    EXPECT_FALSE(mystl_test::deque::DEQUE1.empty());
}

GTEST_TEST(mystl_deque, subscript_operation_access)
{
    EXPECT_EQ(mystl_test::deque::DEQUE1[0], 1);
    EXPECT_EQ(mystl_test::deque::DEQUE1[1], 2);
    EXPECT_EQ(mystl_test::deque::DEQUE1[2], 3);
    EXPECT_EQ(mystl_test::deque::DEQUE1[3], 4);
    EXPECT_EQ(mystl_test::deque::DEQUE1[4], 5);
}

GTEST_TEST(mystl_deque, subscript_operation_modify)
{
    mystl::deque<int> dq = { 1 };
    EXPECT_EQ(dq[0], 1);
    dq[0] = 3;
    EXPECT_EQ(dq[0], 3);
}

GTEST_TEST(mystl_deque, at_access)
{
    EXPECT_EQ(mystl_test::deque::DEQUE1.at(0), 1);
    EXPECT_EQ(mystl_test::deque::DEQUE1.at(1), 2);
    EXPECT_EQ(mystl_test::deque::DEQUE1.at(2), 3);
    EXPECT_EQ(mystl_test::deque::DEQUE1.at(3), 4);
    EXPECT_EQ(mystl_test::deque::DEQUE1.at(4), 5);
}

GTEST_TEST(mystl_deque, at_access_out_of_range)
{
    EXPECT_THROW(mystl_test::deque::DEQUE1.at(6), std::out_of_range);
}

GTEST_TEST(mystl_deque, at_modify)
{
    mystl::deque<int> dq = { 1 };
    EXPECT_EQ(dq.at(0), 1);
    dq.at(0) = 3;
    EXPECT_EQ(dq.at(0), 3);
}

GTEST_TEST(mystl_deque, at_modify_out_of_range)
{
    mystl::deque<int> dq = { 1 };

    EXPECT_THROW(dq.at(3) = 3, std::out_of_range);
}

GTEST_TEST(mystl_deque, push_back)
{
    mystl::deque<int> dq = { 1, 2, 3 };

    dq.push_back(4);
    EXPECT_EQ(dq.size(), 4);
    EXPECT_EQ(dq.back(), 4);

    dq.push_back(5);
    EXPECT_EQ(dq.size(), 5);
    EXPECT_EQ(dq.back(), 5);
}

GTEST_TEST(mystl_deque, pop_back)
{
    mystl::deque<int> dq { 1, 2, 3 };

    dq.pop_back();
    EXPECT_EQ(dq.size(), 2);
    EXPECT_EQ(dq.back(), 2);
    EXPECT_EQ(dq[1], 2);
}

GTEST_TEST(mystl_deque, push_front)
{
    mystl::deque<int> dq;
    dq.push_front(4);
    EXPECT_EQ(dq.front(), 4);
}

GTEST_TEST(mystl_deque, pop_front)
{
    mystl::deque<int> dq { 1, 2, 3 };

    dq.pop_front();
    EXPECT_EQ(dq.size(), 2);
    EXPECT_EQ(dq.front(), 2);
    EXPECT_EQ(dq[1], 3);
}

GTEST_TEST(mystl_deque, clear)
{
    const mystl::vector<int> vec1 = { 1, 2, 4 };
    const mystl::vector<int> vec2;
    const mystl::vector<int> vec3 = { 0 };

    mystl::deque<mystl::vector<int>> dq { vec1, vec2, vec3 };

    dq.clear();
    EXPECT_EQ(dq.size(), 0);
    EXPECT_EQ(dq.begin(), dq.end());
}