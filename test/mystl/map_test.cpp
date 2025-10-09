#include "mystl/map.h"
#include "mystl/string.h"
#include "mystl/utility.h"
#include <gtest/gtest.h>

namespace mystl_test
{
namespace map
{
    const mystl::map<int, int> MP {
        { -5, 2 },
        { 2, 4 },
        { 4, -10 },
        { -10, 6 },
        { 6, 8 },
        {8, 1},

        { 1, 0 },
        {0, 9},
        { 9, -2 }
    };
} // namespace map
} // namespace mystl_test

GTEST_TEST(mystl_map, initialise)
{
    int last = -100;
    for (const auto& [k, v] : mystl_test::map::MP)
    {
        EXPECT_TRUE(k > last);
        last = k;
    }
}

GTEST_TEST(mystl_map, contains)
{
    EXPECT_TRUE(mystl_test::map::MP.contains(0));
    EXPECT_FALSE(mystl_test::map::MP.contains(3));
}

GTEST_TEST(mystl_map, find)
{
    EXPECT_EQ(mystl_test::map::MP.find(-10), mystl_test::map::MP.begin());
    EXPECT_EQ(mystl_test::map::MP.find(100), mystl_test::map::MP.end());
}

GTEST_TEST(mystl_map, upper_bound)
{
    EXPECT_EQ(mystl_test::map::MP.upper_bound(0)->first, 1);
    EXPECT_EQ(mystl_test::map::MP.upper_bound(-10)->first, -5);
    EXPECT_EQ(mystl_test::map::MP.upper_bound(100), mystl_test::map::MP.end());
}

GTEST_TEST(mystl_map, lower_bound)
{
    EXPECT_EQ(mystl_test::map::MP.lower_bound(0)->first, 0);
    EXPECT_EQ(mystl_test::map::MP.lower_bound(-10)->first, -10);
    EXPECT_EQ(mystl_test::map::MP.lower_bound(100), mystl_test::map::MP.end());
}

GTEST_TEST(mystl_map, insert)
{
    mystl::map<int, mystl::string> st { {3,"3"}, {0, "0"}, {5, "5"} };
    EXPECT_FALSE(st.insert({3, "2"}).second);
    EXPECT_EQ(st.insert({1,"5"}).first->first, 1);
}

GTEST_TEST(mystl_map, erase)
{
    mystl::map<int, mystl::string> st { { 3, "3" }, { 0, "0" }, { 5, "5" } };
    EXPECT_EQ(st.erase(3), 1);
    EXPECT_EQ(st.erase(1), 0);
}

GTEST_TEST(mystl_map, size)
{
    mystl::map<int, mystl::string> st { { 3, "3" }, { 0, "0" }, { 5, "5" } };
    EXPECT_EQ(st.size(), 3);
    EXPECT_EQ(mystl_test::map::MP.size(), 9);
}

GTEST_TEST(mystl_map, empty)
{
    mystl::map<int, mystl::string> st;
    EXPECT_TRUE(st.empty());
    EXPECT_FALSE(mystl_test::map::MP.empty());
}

GTEST_TEST(mystl_map, clear)
{
    mystl::map<int, mystl::string> st { { 3, "3" }, { 0, "0" }, { 5, "5" } };
    EXPECT_FALSE(st.empty());
    st.clear();
    EXPECT_TRUE(st.empty());
}