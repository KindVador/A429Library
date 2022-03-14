#include <gtest/gtest.h>
#include "../src/a429bnrword.hpp"

TEST(A429BnrWordTest, DefaultConstructorTest) {
    A429BnrWord wd = A429BnrWord();
    EXPECT_EQ(wd.getLabelAsOctalString(), "000") << "getLabelAsOctalString() returned " << wd.getLabelAsOctalString() << " instead of 000";
    for (int i=1; i<33; ++i)
        EXPECT_FALSE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 0";

    EXPECT_DOUBLE_EQ(wd.getBnrValue(true, 29, 28, 11, 1.0), 0.0);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "00000000") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 00000000";
}


TEST(A429BnrWordTest, IntegerConstructorTest) {
    A429BnrWord wd = A429BnrWord(4294967295, true, true, 29, 28, 11, 1.0);
    EXPECT_EQ(wd.getLabelAsOctalString(), "377") << "get: " << wd.getLabelAsOctalString() << " instead of 377";
    for (int i=1; i<33; ++i)
        EXPECT_TRUE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 1";

    EXPECT_DOUBLE_EQ(wd.getBnrValue(false, 29, 28, 11, 1.0),  262143.0);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "11111111") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 11111111";
}

TEST(A429BnrWordTest, StringConstructorTest) {
    // Hexadecimal String
    A429BnrWord wd = A429BnrWord("FFFFFFFF", true, 16, true, 29, 28, 11, 1.0);
    EXPECT_EQ(wd.getLabelAsOctalString(), "377") << "getLabelAsOctalString() returned " << wd.getLabelAsOctalString() << " instead of 377";
    for (int i=1; i<33; ++i)
        EXPECT_TRUE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 1";

    EXPECT_DOUBLE_EQ(wd.getBnrValue(false, 29, 28, 11, 1.0),  262143.0);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "11111111") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 11111111";

    // Binary String
    wd = A429BnrWord("11111111111111111111111111111111", true, 2, true, 29, 28, 11, 1.0);
    EXPECT_EQ(wd.getLabelAsOctalString(), "377") << "getLabelAsOctalString() returned " << wd.getLabelAsOctalString() << " instead of 377";
    for (int i=1; i<33; ++i)
        EXPECT_TRUE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 1";

    EXPECT_DOUBLE_EQ(wd.getBnrValue(false, 29, 28, 11, 1.0),  262143.0);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "11111111") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 11111111";
    
    // Octal String
    wd = A429BnrWord("37777777777", true, 8, true, 29, 28, 11, 1.0);
    EXPECT_EQ(wd.getLabelAsOctalString(), "377") << "getLabelAsOctalString() returned " << wd.getLabelAsOctalString() << " instead of 377";
    for (int i=1; i<33; ++i)
        EXPECT_TRUE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 1";

    EXPECT_DOUBLE_EQ(wd.getBnrValue(false, 29, 28, 11, 1.0),  262143.0);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "11111111") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 11111111";

    // Decimal String
    wd = A429BnrWord("4294967295", true, 10, true, 29, 28, 11, 1.0);
    EXPECT_EQ(wd.getLabelAsOctalString(), "377") << "getLabelAsOctalString() returned " << wd.getLabelAsOctalString() << " instead of 377";
    for (int i=1; i<33; ++i)
        EXPECT_TRUE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 1";

    EXPECT_DOUBLE_EQ(wd.getBnrValue(false, 29, 28, 11, 1.0),  262143.0);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "11111111") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 11111111";
}

TEST(A429BnrWordTest, GetterIsSigned) {
    A429BnrWord wd = A429BnrWord("FFFFFFFF", true, 16, true, 29, 28, 11, 1.0);
    EXPECT_TRUE(wd.isSigned());
    wd = A429BnrWord("FFFFFFFF", true, 16, false, 29, 28, 11, 1.0);
    EXPECT_FALSE(wd.isSigned());
}

TEST(A429BnrWordTest, SetterIsSigned) {
    A429BnrWord wd = A429BnrWord("FFFFFFFF", true, 16, true, 29, 28, 11, 1.0);
    EXPECT_TRUE(wd.isSigned());
    wd.setIsSigned(false);
    EXPECT_FALSE(wd.isSigned());
    wd = A429BnrWord("FFFFFFFF", true, 16, false, 29, 28, 11, 1.0);
    EXPECT_FALSE(wd.isSigned());
    wd.setIsSigned(true);
    EXPECT_TRUE(wd.isSigned());
}

TEST(A429BnrWordTest, GetterSignBitPosition) {
    A429BnrWord wd = A429BnrWord("FFFFFFFF", true, 16, true, 29, 28, 11, 1.0);
    EXPECT_EQ(wd.signBitPosition(), 29);
    wd = A429BnrWord("FFFFFFFF", true, 16, true, 28, 27, 11, 1.0);
    EXPECT_EQ(wd.signBitPosition(), 28);
}

TEST(A429BnrWordTest, SetterSignBitPosition) {
    A429BnrWord wd = A429BnrWord("FFFFFFFF", true, 16, true, 29, 28, 11, 1.0);
    EXPECT_EQ(wd.signBitPosition(), 29);
    wd.setSignBitPosition(28);
    EXPECT_EQ(wd.signBitPosition(), 28);
    wd.setSignBitPosition(29);
    EXPECT_EQ(wd.signBitPosition(), 29);
}

TEST(A429BnrWordTest, GetterMsbBitPosition) {
    A429BnrWord wd = A429BnrWord("FFFFFFFF", true, 16, true, 29, 28, 11, 1.0);
    EXPECT_EQ(wd.msbBitPosition(), 28);
    wd = A429BnrWord("FFFFFFFF", true, 16, true, 29, 27, 11, 1.0);
    EXPECT_EQ(wd.msbBitPosition(), 27);
}

TEST(A429BnrWordTest, SetterMsbBitPosition) {
    A429BnrWord wd = A429BnrWord("FFFFFFFF", true, 16, true, 29, 28, 11, 1.0);
    EXPECT_EQ(wd.msbBitPosition(), 28);
    wd.setMsbBitPosition(27);
    EXPECT_EQ(wd.msbBitPosition(), 27);
    wd.setMsbBitPosition(28);
    EXPECT_EQ(wd.msbBitPosition(), 28);
}

TEST(A429BnrWordTest, GetterLsbBitPosition) {
    A429BnrWord wd = A429BnrWord("FFFFFFFF", true, 16, true, 29, 28, 11, 1.0);
    EXPECT_EQ(wd.lsbBitPosition(), 11);
    wd = A429BnrWord("FFFFFFFF", true, 16, true, 29, 27, 12, 1.0);
    EXPECT_EQ(wd.lsbBitPosition(), 12);
}

TEST(A429BnrWordTest, SetterLsbBitPosition) {
    A429BnrWord wd = A429BnrWord("FFFFFFFF", true, 16, true, 29, 28, 11, 1.0);
    EXPECT_EQ(wd.lsbBitPosition(), 11);
    wd.setLsbBitPosition(12);
    EXPECT_EQ(wd.lsbBitPosition(), 12);
    wd.setLsbBitPosition(11);
    EXPECT_EQ(wd.lsbBitPosition(), 11);
}

TEST(A429BnrWordTest, GetterResolution) {
    A429BnrWord wd = A429BnrWord("FFFFFFFF", true, 16, true, 29, 28, 11, 1.0);
    EXPECT_EQ(wd.resolution(), 1.0);
    wd = A429BnrWord("FFFFFFFF", true, 16, true, 29, 28, 11, 0.5);
    EXPECT_EQ(wd.resolution(), 0.5);
}

TEST(A429BnrWordTest, SetterResolution) {
    A429BnrWord wd = A429BnrWord("FFFFFFFF", true, 16, true, 29, 28, 11, 1.0);
    EXPECT_EQ(wd.resolution(), 1.0);
    wd.setResolution(0.5);
    EXPECT_EQ(wd.resolution(), 0.5);
    wd.setResolution(1.0);
    EXPECT_EQ(wd.resolution(), 1.0);
}

TEST(A429BnrWordTest, getIndustrialValue) {
    A429BnrWord wd = A429BnrWord("FFFFFFFF", true, 16, true, 29, 28, 11, 1.0);
    EXPECT_DOUBLE_EQ(wd.getIndustrialValue(), -1.0);
    wd = A429BnrWord("FFFFFFFF", true, 16, true, 29, 28, 11, 0.5);
    EXPECT_DOUBLE_EQ(wd.getIndustrialValue(), -0.5);
    wd = A429BnrWord("FFFFFFFF", true, 16, true, 29, 28, 12, 1.0);
    EXPECT_DOUBLE_EQ(wd.getIndustrialValue(), -1.0);
    wd = A429BnrWord("FFFFFFFF", true, 16, true, 29, 27, 11, 1.0);
    EXPECT_DOUBLE_EQ(wd.getIndustrialValue(), -1.0);
    wd = A429BnrWord("FFFFFFFF", true, 16, true, 28, 27, 11, 1.0);
    EXPECT_DOUBLE_EQ(wd.getIndustrialValue(), -1.0);
    wd = A429BnrWord("FFFFFFFF", true, 16, false, 29, 28, 11, 1.0);
    EXPECT_DOUBLE_EQ(wd.getIndustrialValue(), 262143.0);
    wd.setRawValue(std::stoul("EFFFFFFF", nullptr, 16));
    EXPECT_DOUBLE_EQ(wd.getIndustrialValue(), 262143.0);
}