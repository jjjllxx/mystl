#include "mystl/priority_queue.h"
#include "mystl/vector.h"

#include "gtest/gtest.h"

namespace mystl_test
{
namespace priority_queue
{
    const mystl::vector<int>        VEC { 3, 2, 1, 5, 4, 8, 10, 7, 9, 6, 2, 4, 3, 8, 7, 7, 4 };
    const mystl::priority_queue<int> PQ { mystl_test::priority_queue::VEC };
    const mystl::priority_queue<int> EMPTY_PQ;
} // namespace priority_queue
} // namespace mystl_test

GTEST_TEST(mystl_priority_queue, empty)
{
    EXPECT_FALSE(mystl_test::priority_queue::PQ.empty());
    EXPECT_TRUE(mystl_test::priority_queue::EMPTY_PQ.empty());
}

GTEST_TEST(mystl_priority_queue, size)
{
    EXPECT_EQ(mystl_test::priority_queue::EMPTY_PQ.size(), 0);
    EXPECT_EQ(mystl_test::priority_queue::PQ.size(), mystl_test::priority_queue::VEC.size());
}

GTEST_TEST(mystl_priority_queue, top)
{
    EXPECT_EQ(mystl_test::priority_queue::PQ.top(), 10);
}

GTEST_TEST(mystl_priority_queue, pop)
{
    mystl::priority_queue<int> pq { mystl_test::priority_queue::VEC };

    pq.pop();
    EXPECT_EQ(pq.top(), 9);
    EXPECT_EQ(pq.size(), mystl_test::priority_queue::VEC.size() - 1);

    pq.pop();
    EXPECT_EQ(pq.top(), 8);
    EXPECT_EQ(pq.size(), mystl_test::priority_queue::VEC.size() - 2);

    pq.pop();
    EXPECT_EQ(pq.top(), 8);
    EXPECT_EQ(pq.size(), mystl_test::priority_queue::VEC.size() - 3);

    pq.pop();
    EXPECT_EQ(pq.top(), 7);
    EXPECT_EQ(pq.size(), mystl_test::priority_queue::VEC.size() - 4);
}

GTEST_TEST(mystl_priority_queue, push)
{
    mystl::priority_queue<int> pq { mystl_test::priority_queue::VEC };

    pq.push(4);
    EXPECT_EQ(pq.top(), 10);
    EXPECT_EQ(pq.size(), mystl_test::priority_queue::VEC.size() + 1);

    pq.push(12);
    EXPECT_EQ(pq.top(), 12);
    EXPECT_EQ(pq.size(), mystl_test::priority_queue::VEC.size() + 2);

    pq.push(15);
    EXPECT_EQ(pq.top(), 15);
    EXPECT_EQ(pq.size(), mystl_test::priority_queue::VEC.size() + 3);
}

GTEST_TEST(mystl_priority_queue, greater_pop)
{
    mystl::priority_queue<int, mystl::vector<int>, mystl::greater<int>> pq { mystl_test::priority_queue::VEC };

    pq.pop();
    EXPECT_EQ(pq.top(), 2);
    EXPECT_EQ(pq.size(), mystl_test::priority_queue::VEC.size() - 1);

    pq.pop();
    EXPECT_EQ(pq.top(), 2);
    EXPECT_EQ(pq.size(), mystl_test::priority_queue::VEC.size() - 2);

    pq.pop();
    EXPECT_EQ(pq.top(), 3);
    EXPECT_EQ(pq.size(), mystl_test::priority_queue::VEC.size() - 3);

    pq.pop();
    EXPECT_EQ(pq.top(), 3);
    EXPECT_EQ(pq.size(), mystl_test::priority_queue::VEC.size() - 4);
}

GTEST_TEST(mystl_priority_queue, greater_push)
{
    mystl::priority_queue<int, mystl::vector<int>, mystl::greater<int>> pq { mystl_test::priority_queue::VEC };

    pq.push(4);
    EXPECT_EQ(pq.top(), 1);
    EXPECT_EQ(pq.size(), mystl_test::priority_queue::VEC.size() + 1);

    pq.push(-1);
    EXPECT_EQ(pq.top(), -1);
    EXPECT_EQ(pq.size(), mystl_test::priority_queue::VEC.size() + 2);

    pq.push(-2);
    EXPECT_EQ(pq.top(), -2);
    EXPECT_EQ(pq.size(), mystl_test::priority_queue::VEC.size() + 3);
}
