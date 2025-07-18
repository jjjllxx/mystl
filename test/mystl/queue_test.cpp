#include "Queue.h"
#include <gtest/gtest.h>
#include <stdexcept>

GTEST_TEST(DS_Queue, q_empty_true)
{
    dsa::Queue<int> q;

    EXPECT_TRUE(q.empty());
}

GTEST_TEST(DS_Queue, q_empty_false)
{
    dsa::Queue<int> q;
    q.enqueue(2);

    EXPECT_FALSE(q.empty());
}

GTEST_TEST(DS_Queue, q_enqueue)
{
    dsa::Queue<int> q;
    q.enqueue(2);

    EXPECT_EQ(q.dequeue(),2);
}

GTEST_TEST(DS_Queue, q_dequeue)
{
    dsa::Queue<int> q;
    q.enqueue(2);

    EXPECT_EQ(q.dequeue(), 2);
    EXPECT_TRUE(q.empty());
}

GTEST_TEST(DS_Queue, q_dequeue_out_of_range)
{
    dsa::Queue<int> q;

    EXPECT_THROW(q.dequeue(), std::out_of_range);
}

GTEST_TEST(DS_Queue, q_size)
{
    dsa::Queue<int> q;
    EXPECT_EQ(q.size(), 0);
    q.enqueue(2);
    q.enqueue(5);
    q.enqueue(3);
    q.enqueue(4);
    EXPECT_EQ(q.size(), 4);
}

GTEST_TEST(DS_Queue, fsq_empty_true)
{
    dsa::FixedSizeQueue<int> fsq { 4 };

    EXPECT_TRUE(fsq.empty());
}

GTEST_TEST(DS_Queue, fsq_empty_false)
{
    dsa::FixedSizeQueue<int> fsq{4};
    fsq.enqueue(2);

    EXPECT_FALSE(fsq.empty());
}

GTEST_TEST(DS_Queue, fsq_full_true)
{
    dsa::FixedSizeQueue<int> fsq { 4 };
    fsq.enqueue(2);
    fsq.enqueue(5);
    fsq.enqueue(3);
    fsq.enqueue(4);

    EXPECT_TRUE(fsq.full());
}

GTEST_TEST(DS_Queue, fsq_full_false)
{
    dsa::FixedSizeQueue<int> fsq { 4 };
    fsq.enqueue(2);

    EXPECT_FALSE(fsq.full());
}

GTEST_TEST(DS_Queue, fsq_enqueue)
{
    dsa::FixedSizeQueue<int> fsq{4};
    fsq.enqueue(2);

    EXPECT_EQ(fsq.dequeue(), 2);
}

GTEST_TEST(DS_Queue, fsq_enqueue_overflow)
{
    dsa::FixedSizeQueue<int> fsq { 4 };
    fsq.enqueue(2);
    fsq.enqueue(5);
    fsq.enqueue(3);
    fsq.enqueue(4);
    EXPECT_THROW(fsq.enqueue(5), std::overflow_error);
}

GTEST_TEST(DS_Queue, fsq_dequeue)
{
    dsa::FixedSizeQueue<int> fsq { 4 };
    fsq.enqueue(2);

    EXPECT_EQ(fsq.dequeue(), 2);
    EXPECT_TRUE(fsq.empty());
}

GTEST_TEST(DS_Queue, fsq_dequeue_out_of_range)
{
    dsa::FixedSizeQueue<int> q { 4 };

    EXPECT_THROW(q.dequeue(), std::out_of_range);
}