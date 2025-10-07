#include "mystl/set.h"
#include "mystl/string.h"
#include <gtest/gtest.h>

namespace mystl_test
{
namespace set
{
    const mystl::set<int> ST { -5, 2, 4, -10, 6, 8, 1, 0, 9, -2 };
    const mystl::set<mystl::string> STR_ST {"99","0", "7", "1", "10","2", "3" ,"42"};

} // namespace set
} // namespace mystl_test

GTEST_TEST(mystl_set, initialise)
{
    int last = -100;
    for (const int k : mystl_test::set::ST)
    {
        EXPECT_TRUE(k > last);
        last = k;
    }

    mystl::string lasts = "/";
    for (const mystl::string& k : mystl_test::set::STR_ST)
    {
        EXPECT_TRUE(k > lasts);
        lasts = k;
    }
}

GTEST_TEST(mystl_set, contains)
{
    EXPECT_TRUE(mystl_test::set::ST.contains(0));
    EXPECT_FALSE(mystl_test::set::ST.contains(3));
}

GTEST_TEST(mystl_set, find)
{
    EXPECT_EQ(mystl_test::set::ST.find(-10), mystl_test::set::ST.begin());
    EXPECT_EQ(mystl_test::set::ST.find(100), mystl_test::set::ST.end());
}

GTEST_TEST(mystl_set, upper_bound)
{
    EXPECT_EQ(*mystl_test::set::ST.upper_bound(0), 1);
    EXPECT_EQ(*mystl_test::set::ST.upper_bound(-10), -5);
    EXPECT_EQ(mystl_test::set::ST.upper_bound(100), mystl_test::set::ST.end());
}

GTEST_TEST(mystl_set, lower_bound)
{
    EXPECT_EQ(*mystl_test::set::ST.lower_bound(0), 0);
    EXPECT_EQ(*mystl_test::set::ST.lower_bound(-10), -10);
    EXPECT_EQ(mystl_test::set::ST.lower_bound(100), mystl_test::set::ST.end());
}

GTEST_TEST(mystl_set, insert)
{
    mystl::set<int> st{3, 0, 5};   
    EXPECT_FALSE(st.insert(3).second);
    EXPECT_EQ(*st.insert(1).first, 1);
}

GTEST_TEST(mystl_set, erase)
{
    mystl::set<int> st { 3, 0, 5 };
    EXPECT_EQ(st.erase(3), 1);
    EXPECT_EQ(st.erase(1), 0);
}

GTEST_TEST(mystl_set, size)
{
    mystl::set<int> st { 3, 0, 5 };
    EXPECT_EQ(st.size(), 3);
    EXPECT_EQ(mystl_test::set::ST.size(), 10);
}

GTEST_TEST(mystl_set, empty)
{
    mystl::set<int> st;
    EXPECT_TRUE(st.empty());
    EXPECT_FALSE(mystl_test::set::ST.empty());
}

GTEST_TEST(mystl_set, clear)
{
    mystl::set<int> st { 3, 0, 5 };
    EXPECT_FALSE(st.empty());
    st.clear();
    EXPECT_TRUE(st.empty());
}