#include "mystl/queue.h"
#include <gtest/gtest.h>

GTEST_TEST(mystl_queue, q_empty_true)
{
    mystl::queue<int> q;

    EXPECT_TRUE(q.empty());
}

GTEST_TEST(mystl_queue, q_empty_false)
{
    mystl::queue<int> q;
    q.push(2);

    EXPECT_FALSE(q.empty());
}

GTEST_TEST(mystl_queue, q_push)
{
    mystl::queue<int> q;
    q.push(2);
    EXPECT_EQ(q.front(), 2);
}

GTEST_TEST(mystl_queue, front)
{
    mystl::queue<int> q;
    q.push(2);
    q.push(5);
    q.push(3);
    q.push(4);

    EXPECT_EQ(q.front(), 2);
}

GTEST_TEST(mystl_queue, back)
{
    mystl::queue<int> q;
    q.push(2);
    q.push(5);
    q.push(3);
    q.push(4);

    EXPECT_EQ(q.back(), 4);
}

GTEST_TEST(mystl_queue, q_pop)
{
    mystl::queue<int> q;
    q.push(2);

    EXPECT_EQ(q.front(), 2);
    q.pop();
    EXPECT_TRUE(q.empty());
}

GTEST_TEST(mystl_queue, q_size)
{
    mystl::queue<int> q;
    EXPECT_EQ(q.size(), 0);
    q.push(2);
    q.push(5);
    q.push(3);
    q.push(4);
    EXPECT_EQ(q.size(), 4);
}
