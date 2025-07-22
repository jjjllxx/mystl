#include "gtest/gtest.h"

#include "mystl/bitset.h"
#include "mystl/string.h"

namespace dsa_test
{
namespace bitset
{
    const mystl::bitset<8> BITSET_0;
    const mystl::bitset<8> BITSET_42 { 42 };
    const mystl::bitset<8> BITSET_213 { 213 };
    const mystl::bitset<8> BITSET_255 { 255 };

    const mystl::String STR_100       = "1011001000100111110000100011101011111011100000001100101010110110010010000000111011111010101011010110";
    const mystl::String STR_ALL_ONES  = "1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
    const mystl::String STR_ALL_ZEROS = "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
} // namespace Bitset_Test
} // namespace dsa_test

GTEST_TEST(DS_Bitset, initialise)
{
    EXPECT_EQ(dsa_test::bitset::BITSET_0.size(), 8);
    EXPECT_EQ(dsa_test::bitset::BITSET_0.count(), 0);
}

GTEST_TEST(DS_Bitset, initialise_with_value)
{
    EXPECT_EQ(dsa_test::bitset::BITSET_42.size(), 8);
    EXPECT_EQ(dsa_test::bitset::BITSET_42.count(), 3);
    EXPECT_EQ(dsa_test::bitset::BITSET_42.to_uulong(), 42);
}

GTEST_TEST(DS_Array, initialise_with_string)
{
    EXPECT_THROW(
        static_cast<void>(mystl::bitset<6> { "101010", 7 }),
        std::out_of_range);
    EXPECT_THROW(
        static_cast<void>(mystl::bitset<6> { "101010", 2, 6 }),
        std::out_of_range);
    EXPECT_THROW(
        static_cast<void>(mystl::bitset<6> { "101210" }),
        std::invalid_argument);

    const mystl::bitset<6> bs42 { "101010" };
    EXPECT_EQ(bs42.to_uulong(), 42);

    const mystl::bitset<6> bs10 { "101010", 2 };
    EXPECT_EQ(bs10.to_uulong(), 10);

    const mystl::bitset<6> bs21 { "101010", 0, 5 };
    EXPECT_EQ(bs21.to_uulong(), 21);

    const mystl::bitset<6> bsab { "bababa", 0, 6, 'a', 'b' };
    EXPECT_EQ(bsab.to_uulong(), 42);
}

GTEST_TEST(DS_Bitset, set)
{
    mystl::bitset<8> bs { 42 };
    bs.set();
    EXPECT_EQ(bs.to_uulong(), 255);
}

GTEST_TEST(DS_Bitset, set_by_idx_original0)
{
    mystl::bitset<8> bs { 42 };
    bs.set(4);
    EXPECT_EQ(bs.to_uulong(), 58);
}

GTEST_TEST(DS_Bitset, set_by_idx_original1)
{
    mystl::bitset<8> bs { 42 };
    bs.set(5);
    EXPECT_EQ(bs.to_uulong(), 42);
}

GTEST_TEST(DS_Bitset, reset)
{
    mystl::bitset<200> bs = 453721457184587124;
    bs.reset();
    EXPECT_EQ(bs.to_uulong(), 0);
}

GTEST_TEST(DS_Bitset, reset_by_idx_original1)
{
    mystl::bitset<8> bs { 42 };
    bs.reset(5);
    EXPECT_EQ(bs.to_uulong(), 10);
}

GTEST_TEST(DS_Bitset, reset_by_idx_original0)
{
    mystl::bitset<8> bs { 42 };
    bs.reset(4);
    EXPECT_EQ(bs.to_uulong(), 42);
}

GTEST_TEST(DS_Bitset, flip)
{
    mystl::bitset<8> bs { 42 };
    bs.flip();
    EXPECT_EQ(bs.to_uulong(), 213);
    EXPECT_EQ(bs.count(), 5);
}

GTEST_TEST(DS_Bitset, flip_by_idx_original0)
{
    mystl::bitset<8> bs { 42 };
    bs.flip(6);
    EXPECT_EQ(bs.to_uulong(), 106);
    EXPECT_EQ(bs.count(), 4);
}

GTEST_TEST(DS_Bitset, flip_by_idx_original1)
{
    mystl::bitset<8> bs { 42 };
    bs.flip(5);
    EXPECT_EQ(bs.to_uulong(), 10);
    EXPECT_EQ(bs.count(), 2);
}

GTEST_TEST(DS_Bitset, test)
{
    EXPECT_TRUE(dsa_test::bitset::BITSET_42.test(1));
    EXPECT_FALSE(dsa_test::bitset::BITSET_42.test(2));
}

GTEST_TEST(DS_Bitset, any)
{
    EXPECT_FALSE(dsa_test::bitset::BITSET_0.any());
    EXPECT_TRUE(dsa_test::bitset::BITSET_42.any());
}

GTEST_TEST(DS_Bitset, none)
{
    EXPECT_TRUE(dsa_test::bitset::BITSET_0.none());
    EXPECT_FALSE(dsa_test::bitset::BITSET_42.none());
}

GTEST_TEST(DS_Bitset, all)
{
    const mystl::bitset<100> bs { dsa_test::bitset::STR_ALL_ONES };
    EXPECT_TRUE(bs.all());

    const mystl::bitset<101> bs101 { dsa_test::bitset::STR_ALL_ONES };
    EXPECT_FALSE(bs101.all());

    EXPECT_TRUE(dsa_test::bitset::BITSET_255.all());
    EXPECT_FALSE(dsa_test::bitset::BITSET_42.all());
}

GTEST_TEST(DS_Bitset, subscript_operation)
{
    EXPECT_TRUE(dsa_test::bitset::BITSET_42[1]);
    EXPECT_FALSE(dsa_test::bitset::BITSET_42[2]);
}

GTEST_TEST(DS_Bitset, equal_operation)
{
    const mystl::bitset<8> bs { 42 };
    EXPECT_TRUE(dsa_test::bitset::BITSET_42 == bs);
    EXPECT_FALSE(dsa_test::bitset::BITSET_42 == dsa_test::bitset::BITSET_0);
}

GTEST_TEST(DS_Bitset, not_equal_operation)
{
    const mystl::bitset<8> bs { 42 };
    EXPECT_FALSE(dsa_test::bitset::BITSET_42 != bs);
    EXPECT_TRUE(dsa_test::bitset::BITSET_42 != dsa_test::bitset::BITSET_0);
}

GTEST_TEST(DS_Bitset, count)
{
    EXPECT_EQ(dsa_test::bitset::BITSET_42.count(), 3);
    EXPECT_EQ(dsa_test::bitset::BITSET_0.count(), 0);
}

GTEST_TEST(DS_Bitset, size)
{
    EXPECT_EQ(dsa_test::bitset::BITSET_42.size(), 8);
    EXPECT_EQ(dsa_test::bitset::BITSET_0.size(), 8);
}

GTEST_TEST(DS_Bitset, to_uulong)
{
    const mystl::bitset<100> bs_long { dsa_test::bitset::STR_100 };
    EXPECT_THROW(bs_long.to_uulong(), std::overflow_error);
    EXPECT_EQ(dsa_test::bitset::BITSET_0.to_uulong(), 0);
}

GTEST_TEST(DS_Bitset, to_string)
{
    const mystl::bitset<100> bs_long { dsa_test::bitset::STR_100 };
    EXPECT_EQ(bs_long.to_string(), dsa_test::bitset::STR_100);
    EXPECT_EQ(dsa_test::bitset::BITSET_0.to_string(), "00000000");
    EXPECT_EQ(dsa_test::bitset::BITSET_42.to_string(), "00101010");
}

GTEST_TEST(DS_Bitset, and_operation)
{
    EXPECT_EQ((dsa_test::bitset::BITSET_0 & dsa_test::bitset::BITSET_42).to_uulong(), 0);
    EXPECT_EQ((dsa_test::bitset::BITSET_255 & dsa_test::bitset::BITSET_42).to_uulong(), 42);
}

GTEST_TEST(DS_Bitset, or_operation)
{
    EXPECT_EQ((dsa_test::bitset::BITSET_0 | dsa_test::bitset::BITSET_42).to_uulong(), 42);
    EXPECT_EQ((dsa_test::bitset::BITSET_213 | dsa_test::bitset::BITSET_42).to_uulong(), 255);
}

GTEST_TEST(DS_Bitset, xor_operation)
{
    EXPECT_EQ((dsa_test::bitset::BITSET_0 ^ dsa_test::bitset::BITSET_42).to_uulong(), 42);
    EXPECT_EQ((dsa_test::bitset::BITSET_255 ^ dsa_test::bitset::BITSET_42).to_uulong(), 213);
}

GTEST_TEST(DS_Bitset, not_operation)
{
    const mystl::bitset<100> bs1 { dsa_test::bitset::STR_ALL_ONES };
    const mystl::bitset<100> bs0 { dsa_test::bitset::STR_ALL_ZEROS };

    EXPECT_EQ(~bs1, bs0);
    EXPECT_EQ(~bs0, bs1);
    EXPECT_EQ(~dsa_test::bitset::BITSET_0, dsa_test::bitset::BITSET_255);
    EXPECT_EQ(~dsa_test::bitset::BITSET_42, dsa_test::bitset::BITSET_213);
}

GTEST_TEST(DS_Bitset, left_shift_operation)
{
    EXPECT_EQ(dsa_test::bitset::BITSET_0 << 2, dsa_test::bitset::BITSET_0);
    EXPECT_EQ((dsa_test::bitset::BITSET_42 << 2).to_uulong(), 168);
    EXPECT_EQ((dsa_test::bitset::BITSET_255 << 2).to_uulong(), 252);

    const mystl::bitset<100> bs_long { dsa_test::bitset::STR_100 };
    EXPECT_EQ((bs_long << 3).to_string(), "1001000100111110000100011101011111011100000001100101010110110010010000000111011111010101011010110000");
}

GTEST_TEST(DS_Bitset, right_shift_operation)
{
    EXPECT_EQ(dsa_test::bitset::BITSET_0 >> 2, dsa_test::bitset::BITSET_0);
    EXPECT_EQ((dsa_test::bitset::BITSET_42 >> 2).to_uulong(), 10);
    EXPECT_EQ((dsa_test::bitset::BITSET_255 >> 2).to_uulong(), 63);

    const mystl::bitset<100> bs_long { dsa_test::bitset::STR_100 };
    EXPECT_EQ((bs_long >> 3).to_string(), "0001011001000100111110000100011101011111011100000001100101010110110010010000000111011111010101011010");
}