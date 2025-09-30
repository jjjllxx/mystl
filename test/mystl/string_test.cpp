#include "mystl/string.h"
#include <gtest/gtest.h>

namespace mystl_test
{
namespace string
{
    const mystl::string EMPTY_STRING;
    const mystl::string SHORT_STRING = "apple";
    const mystl::string LONG_STRING  = "this is a very long sentence";
} // namespace string
} // namespace mystl_test

GTEST_TEST(mystl_string, initialise_empty)
{
    EXPECT_TRUE(mystl_test::string::EMPTY_STRING.empty());
    EXPECT_EQ(mystl_test::string::EMPTY_STRING.capacity(), mystl::STRING_INITIAL_CAPACITY);
}

GTEST_TEST(mystl_string, initialise_short)
{
    EXPECT_EQ(mystl_test::string::SHORT_STRING.size(), 5);
    EXPECT_EQ(mystl_test::string::SHORT_STRING.capacity(), mystl::STRING_INITIAL_CAPACITY);
}

GTEST_TEST(mystl_string, initialise_long)
{
    EXPECT_EQ(mystl_test::string::LONG_STRING.size(), 28);
    EXPECT_EQ(mystl_test::string::LONG_STRING.capacity(), mystl_test::string::LONG_STRING.size());
}

GTEST_TEST(mystl_string, size)
{
    EXPECT_EQ(mystl_test::string::LONG_STRING.size(), 28);
}

GTEST_TEST(mystl_string, capacity)
{
    EXPECT_EQ(mystl_test::string::LONG_STRING.capacity(), mystl_test::string::LONG_STRING.size());
}

GTEST_TEST(mystl_string, empty_true)
{
    EXPECT_TRUE(mystl_test::string::EMPTY_STRING.empty());
}

GTEST_TEST(mystl_string, empty_false)
{
    EXPECT_FALSE(mystl_test::string::LONG_STRING.empty());
}

GTEST_TEST(mystl_string, back)
{
    EXPECT_EQ(mystl_test::string::LONG_STRING.back(), 'e');
}

GTEST_TEST(mystl_string, push_back)
{
    mystl::string s = "apple";
    s.push_back('s');
    EXPECT_EQ(s.size(), 6);
    EXPECT_EQ(s.back(), 's');
}

GTEST_TEST(mystl_string, push_back_with_capacity_increasing)
{
    mystl::string s = "apple bananacat";
    EXPECT_EQ(s.capacity(), s.size());
    EXPECT_EQ(s.capacity(), mystl::STRING_INITIAL_CAPACITY);
    s.push_back('s');
    EXPECT_EQ(s.capacity(), mystl::STRING_INITIAL_CAPACITY << 1);
    EXPECT_EQ(s.back(), 's');
}

GTEST_TEST(mystl_string, pop_back)
{
    mystl::string s = "apple";
    EXPECT_EQ(s.pop_back(), 'e');
    EXPECT_EQ(s.size(), 4);
    EXPECT_EQ(s.back(), 'l');
}

GTEST_TEST(mystl_string, reserve)
{
    mystl::string s = "apple";
    s.reserve(20);
    EXPECT_EQ(s.capacity(), 20);
    s.reserve(3);
    EXPECT_EQ(s.capacity(), 20);
}

GTEST_TEST(mystl_string, subscript_operation_access)
{
    EXPECT_EQ(mystl_test::string::SHORT_STRING[0], 'a');
    EXPECT_EQ(mystl_test::string::SHORT_STRING[1], 'p');
    EXPECT_EQ(mystl_test::string::SHORT_STRING[2], 'p');
    EXPECT_EQ(mystl_test::string::SHORT_STRING[3], 'l');
    EXPECT_EQ(mystl_test::string::SHORT_STRING[4], 'e');
}

GTEST_TEST(mystl_string, subscript_operation_modify)
{
    mystl::string s = "123";
    EXPECT_EQ(s[0], '1');
    s[0] = 'a';
    EXPECT_EQ(s[0], 'a');
}

GTEST_TEST(mystl_string, equality_operator_different_size)
{
    EXPECT_FALSE(mystl_test::string::SHORT_STRING == mystl_test::string::LONG_STRING);
}

GTEST_TEST(mystl_string, equality_operator_same_size_false)
{
    EXPECT_FALSE(mystl_test::string::SHORT_STRING == "appla");
}

GTEST_TEST(mystl_string, equality_operator_true)
{
    EXPECT_TRUE(mystl_test::string::SHORT_STRING == "apple");
}