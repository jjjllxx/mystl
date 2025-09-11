#include <gtest/gtest.h>

#include "mystl/deque.h"
#include "mystl/stack.h"
#include "gtest/gtest.h"

namespace mystl_test
{
namespace stack
{
    const mystl::stack<int> EMPTY_DEQUE;
    const mystl::stack<int> DEQUE1 { mystl::deque<int> { 1, 2, 3, 4, 5 } };
} // namespace stack
} // namespace mystl_test

GTEST_TEST(mystl_stack, initialise_empty)
{
    EXPECT_TRUE(mystl_test::stack::EMPTY_DEQUE.empty());
}

GTEST_TEST(mystl_stack, initialise_with_deque)
{
    EXPECT_EQ(mystl_test::stack::DEQUE1.size(), 5);
}

GTEST_TEST(mystl_stack, top)
{
    EXPECT_EQ(mystl_test::stack::DEQUE1.top(), 5);
}

GTEST_TEST(mystl_stack, size)
{
    EXPECT_EQ(mystl_test::stack::DEQUE1.size(), 5);
    EXPECT_EQ(mystl_test::stack::EMPTY_DEQUE.size(), 0);
}

GTEST_TEST(mystl_stack, empty)
{
    EXPECT_TRUE(mystl_test::stack::EMPTY_DEQUE.empty());
    EXPECT_FALSE(mystl_test::stack::DEQUE1.empty());
}

GTEST_TEST(mystl_stack, push_back)
{
    mystl::stack<int> stk { mystl::deque<int> { 1, 2, 3 } };

    stk.push(4);
    EXPECT_EQ(stk.size(), 4);
    EXPECT_EQ(stk.top(), 4);

    stk.push(5);
    EXPECT_EQ(stk.size(), 5);
    EXPECT_EQ(stk.top(), 5);
}

GTEST_TEST(mystl_stack, pop)
{
    mystl::stack<int> stk { mystl::deque<int> { 1, 2, 3 } };

    EXPECT_EQ(stk.top(), 3);
    stk.pop();
    EXPECT_EQ(stk.size(), 2);
    EXPECT_EQ(stk.top(), 2);
}