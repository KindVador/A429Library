#include <gtest/gtest.h>
#include "../a429bnrword.hpp"

TEST(A429BnrWordTest, DefaultConstructorTest) {
    A429BnrWord wd = A429BnrWord();
    EXPECT_EQ(wd.getLabelAsOctalString(), "000") << "getLabelAsOctalString() returned " << wd.getLabelAsOctalString() << " instead of 000";
    for (int i=1; i<33; ++i) {
        EXPECT_FALSE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 0";
    }
    EXPECT_DOUBLE_EQ(wd.getBnrValue(true, 29, 28, 11, 1.0), 0.0);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "00000000") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 00000000";
}


TEST(A429BnrWordTest, IntegerConstructorTest) {
    A429BnrWord wd = A429BnrWord(4294967295, true, true, 29, 28, 11, 1.0);
    EXPECT_EQ(wd.getLabelAsOctalString(), "377") << "get: " << wd.getLabelAsOctalString() << " instead of 377";
    for (int i=1; i<33; ++i) {
        EXPECT_TRUE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 1";
    }
    EXPECT_DOUBLE_EQ(wd.getBnrValue(false, 29, 28, 11, 1.0),  262143.0);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "11111111") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 11111111";
}

TEST(A429BnrWordTest, StringConstructorTest) {
    // Hexadecimal String
    A429BnrWord wd = A429BnrWord("FFFFFFFF", true, 16, true, 29, 28, 11, 1.0);
    EXPECT_EQ(wd.getLabelAsOctalString(), "377") << "getLabelAsOctalString() returned " << wd.getLabelAsOctalString() << " instead of 377";
    for (int i=1; i<33; ++i) {
        EXPECT_TRUE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 1";
    }
    EXPECT_DOUBLE_EQ(wd.getBnrValue(false, 29, 28, 11, 1.0),  262143.0);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "11111111") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 11111111";

    // Binary String
    wd = A429BnrWord("11111111111111111111111111111111", true, 2, true, 29, 28, 11, 1.0);
    EXPECT_EQ(wd.getLabelAsOctalString(), "377") << "getLabelAsOctalString() returned " << wd.getLabelAsOctalString() << " instead of 377";
    for (int i=1; i<33; ++i) {
        EXPECT_TRUE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 1";
    }
    EXPECT_DOUBLE_EQ(wd.getBnrValue(false, 29, 28, 11, 1.0),  262143.0);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "11111111") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 11111111";
    
    // Octal String
    wd = A429BnrWord("37777777777", true, 8, true, 29, 28, 11, 1.0);
    EXPECT_EQ(wd.getLabelAsOctalString(), "377") << "getLabelAsOctalString() returned " << wd.getLabelAsOctalString() << " instead of 377";
    for (int i=1; i<33; ++i) {
        EXPECT_TRUE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 1";
    }
    EXPECT_DOUBLE_EQ(wd.getBnrValue(false, 29, 28, 11, 1.0),  262143.0);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "11111111") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 11111111";

    // Decimal String
    wd = A429BnrWord("4294967295", true, 10, true, 29, 28, 11, 1.0);
    EXPECT_EQ(wd.getLabelAsOctalString(), "377") << "getLabelAsOctalString() returned " << wd.getLabelAsOctalString() << " instead of 377";
    for (int i=1; i<33; ++i) {
        EXPECT_TRUE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 1";
    }
    EXPECT_DOUBLE_EQ(wd.getBnrValue(false, 29, 28, 11, 1.0),  262143.0);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "11111111") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 11111111";
}
