#include <gtest/gtest.h>
#include "../a429word.hpp"

TEST(A429WordTest, DefaultConstructorTest) {
    A429Word wd = A429Word();
    EXPECT_EQ(wd.getLabelAsOctalString(), "000") << "getLabelAsOctalString() returned " << wd.getLabelAsOctalString() << " instead of 000";
    for (int i=1; i<33; ++i) {
        EXPECT_FALSE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 0";
    }
    EXPECT_DOUBLE_EQ(wd.getBnrValue(true, 29, 28, 11, 1.0), 0.0);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "00000000") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 00000000";
}

TEST(A429WordTest, IntegerConstructorTest) {
    A429Word wd = A429Word(4294967295, true);
    EXPECT_EQ(wd.getLabelAsOctalString(), "377") << "get: " << wd.getLabelAsOctalString() << " instead of 377";
    for (int i=1; i<33; ++i) {
        EXPECT_TRUE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 1";
    }
    EXPECT_DOUBLE_EQ(wd.getBnrValue(false, 29, 28, 11, 1.0),  262143.0);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "11111111") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 11111111";
}

TEST(A429WordTest, StringConstructorTest) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    EXPECT_EQ(wd.getLabelAsOctalString(), "377") << "getLabelAsOctalString() returned " << wd.getLabelAsOctalString() << " instead of 377";
    for (int i=1; i<33; ++i) {
        EXPECT_TRUE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 1";
    }
    EXPECT_DOUBLE_EQ(wd.getBnrValue(false, 29, 28, 11, 1.0),  262143.0);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "11111111") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 11111111";
}

TEST(A429WordTest, GetterRawValue) {
    A429Word wd = A429Word("ABCD2234", true, 16);
    EXPECT_EQ(wd.rawValue(), std::stol("ABCD2234", nullptr, 16));
}

TEST(A429WordTest, SetterRawValue) {
    A429Word wd = A429Word("ABCD2234", true, 16);
    EXPECT_EQ(wd.rawValue(), std::stol("ABCD2234", nullptr, 16));
    // set a new raw value
    wd.setRawValue(2249354846);
    EXPECT_EQ(wd.rawValue(), 2249354846);
    EXPECT_EQ(wd.labelNumber(), 94);
    EXPECT_EQ(wd.sdi(), 2);
    EXPECT_EQ(wd.ssm(), 0);
    //EXPECT_EQ(wd.parity(), 1);
    // set a new raw value
    wd.setRawValue(std::stol("123417CD", nullptr, 16));
    EXPECT_EQ(wd.rawValue(), 305403853);
    EXPECT_EQ(wd.labelNumber(), 205);
    EXPECT_EQ(wd.sdi(), 3);
    EXPECT_EQ(wd.ssm(), 0);
    //EXPECT_EQ(wd.parity(), 0);
}

TEST(A429WordTest, GetterLabelNumber) {
    A429Word wd = A429Word("123417CD", true, 16);
    EXPECT_EQ(wd.labelNumber(), 205);
}

TEST(A429WordTest, SetterLabelNumber) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    EXPECT_EQ(wd.labelNumber(), 255);
    for(int i=0; i<256; ++i) {
        wd.setLabelNumber(i);
        EXPECT_EQ(wd.labelNumber(), i);
    }
}

TEST(A429WordTest, GetterSdi) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    EXPECT_EQ(wd.sdi(), 3);
    wd.setRawValue(std::stol("FFFFFEFF", nullptr, 16));
    EXPECT_EQ(wd.sdi(), 2);
    wd.setRawValue(std::stol("FFFFFDFF", nullptr, 16));
    EXPECT_EQ(wd.sdi(), 1);
    wd.setRawValue(std::stol("FFFFFCFF", nullptr, 16));
    EXPECT_EQ(wd.sdi(), 0);
}

TEST(A429WordTest, SetterSdi) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    EXPECT_EQ(wd.sdi(), 3);
    for(int i=0; i<4; ++i) {
        wd.setSdi(i);
        EXPECT_EQ(wd.sdi(), i);
    }
}

TEST(A429WordTest, GetterPayload) {
    A429Word wd = A429Word("ABCD2234", true, 16);
    EXPECT_EQ(wd.payload(), std::stoi("0101111001101001000", nullptr, 2));

}

TEST(A429WordTest, SetterPayload) {
    A429Word wd = A429Word("ABCD2234", true, 16);
    EXPECT_EQ(wd.payload(), std::stoi("0101111001101001000", nullptr, 2));
    // maximum value
    wd.setPayload(524287);
    EXPECT_EQ(wd.payload(), std::stoi("1111111111111111111", nullptr, 2));
    // minimum value
    wd.setPayload(0);
    EXPECT_EQ(wd.payload(), std::stoi("0000000000000000000", nullptr, 2));
    // test all possible values
    for(int i=0; i<524288; ++i) {
        wd.setPayload(i);
        EXPECT_EQ(wd.payload(), i);
    }
}

TEST(A429WordTest, GetterSsm) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    EXPECT_EQ(wd.ssm(), 3);
    wd.setRawValue(std::stol("DFFFFFFF", nullptr, 16));
    EXPECT_EQ(wd.ssm(), 2);
    wd.setRawValue(std::stol("BFFFFFFF", nullptr, 16));
    EXPECT_EQ(wd.ssm(), 1);
    wd.setRawValue(std::stol("9FFFFFFF", nullptr, 16));
    EXPECT_EQ(wd.ssm(), 0);
}

TEST(A429WordTest, SetterSsm) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    EXPECT_EQ(wd.ssm(), 3);
    for(int i=0; i<4; ++i) {
        wd.setSsm(i);
        EXPECT_EQ(wd.ssm(), i);
    }
}

TEST(A429WordTest, GetterParity) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    EXPECT_EQ(wd.parity(), 1);
    wd.setRawValue(std::stol("7FFFFFFF", nullptr, 16));
    EXPECT_EQ(wd.parity(), 0);
}

TEST(A429WordTest, SetterParity) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    EXPECT_EQ(wd.parity(), 1);
    wd.setParity(false);
    EXPECT_EQ(wd.parity(), 0);
    wd.setParity(true);
    EXPECT_EQ(wd.parity(), 1);
}

TEST(A429WordTest, GetterLabelNumberMsbFirst) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    EXPECT_EQ(wd.labelNumberMsbFirst(), 1);
    wd = A429Word("FFFFFFFF", false, 16);
    EXPECT_EQ(wd.labelNumberMsbFirst(), 0);
}

TEST(A429WordTest, SetterLabelNumberMsbFirst) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    EXPECT_EQ(wd.labelNumberMsbFirst(), true);
    wd.setLabelNumberMsbFirst(false);
    EXPECT_EQ(wd.labelNumberMsbFirst(), false);
    wd.setLabelNumberMsbFirst(true);
    EXPECT_EQ(wd.labelNumberMsbFirst(), true);
}

TEST(A429WordTest, getLabelAsBinaryString) {
    // CASE LABEL 377 (ALL BITS TO 1)
    A429Word wd = A429Word("FFFFFFFF", false, 16);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "11111111") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 11111111";
    EXPECT_EQ(wd.getLabelAsBinaryString(false), "11111111") << "getLabelAsBinaryString(false) returned " << wd.getLabelAsBinaryString(false) << " instead of 11111111";
    // CASE LABEL 000 (ALL BITS TO 0)
    wd = A429Word("FFFFFF00", false, 16);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "00000000") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 00000000";
    EXPECT_EQ(wd.getLabelAsBinaryString(false), "00000000") << "getLabelAsBinaryString(false) returned " << wd.getLabelAsBinaryString(false) << " instead of 00000000";
    // CASE LABEL 254 AND 065
    wd = A429Word("FFFFFF35", false, 16);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "10101100") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 10101100";
    EXPECT_EQ(wd.getLabelAsBinaryString(false), "00110101") << "getLabelAsBinaryString(false) returned " << wd.getLabelAsBinaryString(false) << " instead of 00110101";
    // CASE LABEL 256 AND 165
    wd = A429Word("FFFFFF75", false, 16);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "01110101") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 01110101";
    EXPECT_EQ(wd.getLabelAsBinaryString(false), "10101110") << "getLabelAsBinaryString(false) returned " << wd.getLabelAsBinaryString(false) << " instead of 10101110";
}

TEST(A429WordTest, getBit) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    FAIL();
}

TEST(A429WordTest, setBit) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    FAIL();
}

TEST(A429WordTest, toBinaryString) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    FAIL();
}

TEST(A429WordTest, getLabelAsOctalString) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    FAIL();
}

TEST(A429WordTest, getBnrValue) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    FAIL();
}

TEST(A429WordTest, isParityValid) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    FAIL();
}

TEST(A429WordTest, toggleBit) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    FAIL();
}