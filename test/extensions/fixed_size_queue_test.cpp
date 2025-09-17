#include "extensions/fixed_size_queue.h"
#include <gtest/gtest.h>

GTEST_TEST(ext_fsq, fsq_empty_true)
{
    ext::fixed_size_queue<int> fsq { 4 };

    EXPECT_TRUE(fsq.empty());
}

GTEST_TEST(ext_fsq, fsq_empty_false)
{
    ext::fixed_size_queue<int> fsq{4};
    fsq.push(2);

    EXPECT_FALSE(fsq.empty());
}

GTEST_TEST(ext_fsq, fsq_full_true)
{
    ext::fixed_size_queue<int> fsq { 4 };
    fsq.push(2);
    fsq.push(5);
    fsq.push(3);
    fsq.push(4);

    EXPECT_TRUE(fsq.full());
}

GTEST_TEST(ext_fsq, fsq_full_false)
{
    ext::fixed_size_queue<int> fsq { 4 };
    fsq.push(2);

    EXPECT_FALSE(fsq.full());
}

GTEST_TEST(ext_fsq, fsq_push)
{
    ext::fixed_size_queue<int> fsq{4};
    fsq.push(2);

    EXPECT_EQ(fsq.front(), 2);
}

GTEST_TEST(ext_fsq, fsq_enqueue_overflow)
{
    ext::fixed_size_queue<int> fsq { 4 };
    fsq.push(2);
    fsq.push(5);
    fsq.push(3);
    fsq.push(4);
    EXPECT_THROW(fsq.push(5), std::overflow_error);
}

GTEST_TEST(ext_fsq, fsq_pop)
{
    ext::fixed_size_queue<int> fsq { 4 };
    fsq.push(2);

    fsq.pop();
    EXPECT_TRUE(fsq.empty());
}