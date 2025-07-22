#include "mystl/queue.h"
#include <gtest/gtest.h>
#include <stdexcept>

GTEST_TEST(DS_Queue, q_empty_true)
{
    mystl::queue<int> q;

    EXPECT_TRUE(q.empty());
}

GTEST_TEST(DS_Queue, q_empty_false)
{
    mystl::queue<int> q;
    q.enqueue(2);

    EXPECT_FALSE(q.empty());
}

GTEST_TEST(DS_Queue, q_enqueue)
{
    mystl::queue<int> q;
    q.enqueue(2);

    EXPECT_EQ(q.dequeue(),2);
}

GTEST_TEST(DS_Queue, q_dequeue)
{
    mystl::queue<int> q;
    q.enqueue(2);

    EXPECT_EQ(q.dequeue(), 2);
    EXPECT_TRUE(q.empty());
}

GTEST_TEST(DS_Queue, q_dequeue_out_of_range)
{
    mystl::queue<int> q;

    EXPECT_THROW(q.dequeue(), std::out_of_range);
}

GTEST_TEST(DS_Queue, q_size)
{
    mystl::queue<int> q;
    EXPECT_EQ(q.size(), 0);
    q.enqueue(2);
    q.enqueue(5);
    q.enqueue(3);
    q.enqueue(4);
    EXPECT_EQ(q.size(), 4);
}

GTEST_TEST(DS_Queue, fsq_empty_true)
{
    mystl::FixedSizeQueue<int> fsq { 4 };

    EXPECT_TRUE(fsq.empty());
}

GTEST_TEST(DS_Queue, fsq_empty_false)
{
    mystl::FixedSizeQueue<int> fsq { 4 };
    fsq.enqueue(2);

    EXPECT_FALSE(fsq.empty());
}

GTEST_TEST(DS_Queue, fsq_full_true)
{
    mystl::FixedSizeQueue<int> fsq { 4 };
    fsq.enqueue(2);
    fsq.enqueue(5);
    fsq.enqueue(3);
    fsq.enqueue(4);

    EXPECT_TRUE(fsq.full());
}

GTEST_TEST(DS_Queue, fsq_full_false)
{
    mystl::FixedSizeQueue<int> fsq { 4 };
    fsq.enqueue(2);

    EXPECT_FALSE(fsq.full());
}

GTEST_TEST(DS_Queue, fsq_enqueue)
{
    mystl::FixedSizeQueue<int> fsq { 4 };
    fsq.enqueue(2);

    EXPECT_EQ(fsq.dequeue(), 2);
}

GTEST_TEST(DS_Queue, fsq_enqueue_overflow)
{
    mystl::FixedSizeQueue<int> fsq { 4 };
    fsq.enqueue(2);
    fsq.enqueue(5);
    fsq.enqueue(3);
    fsq.enqueue(4);
    EXPECT_THROW(fsq.enqueue(5), std::overflow_error);
}

GTEST_TEST(DS_Queue, fsq_dequeue)
{
    mystl::FixedSizeQueue<int> fsq { 4 };
    fsq.enqueue(2);

    EXPECT_EQ(fsq.dequeue(), 2);
    EXPECT_TRUE(fsq.empty());
}

GTEST_TEST(DS_Queue, fsq_dequeue_out_of_range)
{
    mystl::FixedSizeQueue<int> q { 4 };

    EXPECT_THROW(q.dequeue(), std::out_of_range);
}