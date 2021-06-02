#include <gtest/gtest.h>
#include "../a429word.hpp"
#include <cstdio>
#include <algorithm>
#include <bitset>

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
    // Hexadecimal String
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    EXPECT_EQ(wd.getLabelAsOctalString(), "377") << "getLabelAsOctalString() returned " << wd.getLabelAsOctalString() << " instead of 377";
    for (int i=1; i<33; ++i) {
        EXPECT_TRUE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 1";
    }
    EXPECT_DOUBLE_EQ(wd.getBnrValue(false, 29, 28, 11, 1.0),  262143.0);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "11111111") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 11111111";

    // Binary String
    wd = A429Word("11111111111111111111111111111111", true, 2);
    EXPECT_EQ(wd.getLabelAsOctalString(), "377") << "getLabelAsOctalString() returned " << wd.getLabelAsOctalString() << " instead of 377";
    for (int i=1; i<33; ++i) {
        EXPECT_TRUE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 1";
    }
    EXPECT_DOUBLE_EQ(wd.getBnrValue(false, 29, 28, 11, 1.0),  262143.0);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "11111111") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 11111111";
    
    // Octal String
    wd = A429Word("37777777777", true, 8);
    EXPECT_EQ(wd.getLabelAsOctalString(), "377") << "getLabelAsOctalString() returned " << wd.getLabelAsOctalString() << " instead of 377";
    for (int i=1; i<33; ++i) {
        EXPECT_TRUE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 1";
    }
    EXPECT_DOUBLE_EQ(wd.getBnrValue(false, 29, 28, 11, 1.0),  262143.0);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "11111111") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 11111111";

    // Decimal String
    wd = A429Word("4294967295", true, 10);
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
    EXPECT_EQ(wd.parity(), 1);
    // set a new raw value
    wd.setRawValue(std::stol("123417CD", nullptr, 16));
    EXPECT_EQ(wd.rawValue(), 305403853);
    EXPECT_EQ(wd.labelNumber(), 205);
    EXPECT_EQ(wd.sdi(), 3);
    EXPECT_EQ(wd.ssm(), 0);
    EXPECT_EQ(wd.parity(), 0);
    // out_of_range exception
    // This exception cannot be tested because the compiler performs an implicitly conversion from long to int which changes the value
    // EXPECT_THROW(wd.setRawValue(4294967296), std::out_of_range);
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
    // out_of_range exception
    EXPECT_THROW(wd.setLabelNumber(256), std::out_of_range);
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
    // out_of_range exception
    EXPECT_THROW(wd.setSdi(4), std::out_of_range);
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
    // out_of_range exception
    EXPECT_THROW(wd.setPayload(524288), std::out_of_range);
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
    // out_of_range exception
    EXPECT_THROW(wd.setSsm(256), std::out_of_range);
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
    wd = A429Word("FFFFFF75", true, 16);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "01110101") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 01110101";
    EXPECT_EQ(wd.getLabelAsBinaryString(false), "10101110") << "getLabelAsBinaryString(false) returned " << wd.getLabelAsBinaryString(false) << " instead of 10101110";
}

TEST(A429WordTest, getBit) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    // all bits set to 1
    for (int i=1; i<33; ++i) {
        EXPECT_TRUE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 1";
    }
    // all bits set to 0
    wd.setRawValue(std::stol("00000000", nullptr, 16));
    for (int i=1; i<33; ++i) {
        EXPECT_FALSE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 0";
    }
    // alternate between 0 and 1
    wd.setRawValue(std::stol("AAAAAAAA", nullptr, 16));
    for (int i=1; i<33; ++i) {
        if (i % 2 == 0) {
            EXPECT_TRUE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 1";
        } else {
            EXPECT_FALSE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 0";
        }
    }
    // out_of_range exception
    EXPECT_THROW(wd.getBit(33), std::out_of_range);
}

TEST(A429WordTest, setBit) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    // set all bits to 0
    for (int i=1; i<33; ++i) {
        wd.setBit(i, false);
        EXPECT_FALSE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 0";
    }
    // set all bits to 1
    for (int i=1; i<33; ++i) {
        wd.setBit(i, true);
        EXPECT_TRUE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 1";
    }
    // out_of_range exception
    EXPECT_THROW(wd.setBit(33, true), std::out_of_range);
}

TEST(A429WordTest, toBinaryString) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    EXPECT_EQ(wd.toBinaryString(), "11111111111111111111111111111111");
    wd.setRawValue(std::stol("00000000", nullptr, 16));
    EXPECT_EQ(wd.toBinaryString(), "00000000000000000000000000000000");
    wd.setRawValue(std::stol("AAAAAAAA", nullptr, 16));
    EXPECT_EQ(wd.toBinaryString(), "10101010101010101010101010101010");
    wd.setRawValue(std::stol("55555555", nullptr, 16));
    EXPECT_EQ(wd.toBinaryString(), "01010101010101010101010101010101");
}

TEST(A429WordTest, getLabelAsOctalString) {
    // tests with label_number_msb_first option set to True
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    for (int i = 0; i < 256; ++i) {
        wd.setLabelNumber(i);
        std::string labelString = std::bitset<8>(i).to_string();
        std::reverse(labelString.begin(), labelString.end());
        unsigned short labelInt = std::stoi(labelString, nullptr, 2);
        char buffer[4];
        int n = sprintf(buffer, "%03o", labelInt);
        EXPECT_EQ(wd.getLabelAsOctalString(), std::string(buffer));
    }

    // tests with label_number_msb_first option set to False
    wd = A429Word("FFFFFFFF", false, 16);
    for (int i = 0; i < 256; ++i) {
        wd.setLabelNumber(i);
        std::string labelString = std::bitset<8>(i).to_string();
        unsigned short labelInt = std::stoi(labelString, nullptr, 2);
        char buffer[4];
        int n = sprintf(buffer, "%03o", labelInt);
        EXPECT_EQ(wd.getLabelAsOctalString(), std::string(buffer));
    }
}

TEST(A429WordTest, getBnrValue) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    EXPECT_DOUBLE_EQ(wd.getBnrValue(true, 29, 28, 11, 1.0), -1.0);
    EXPECT_DOUBLE_EQ(wd.getBnrValue(true, 29, 28, 11, 0.5), -0.5);
    EXPECT_DOUBLE_EQ(wd.getBnrValue(true, 29, 28, 12, 1.0), -1.0);
    EXPECT_DOUBLE_EQ(wd.getBnrValue(true, 29, 27, 11, 1.0), -1.0);
    EXPECT_DOUBLE_EQ(wd.getBnrValue(true, 28, 27, 11, 1.0), -1.0);
    EXPECT_DOUBLE_EQ(wd.getBnrValue(false, 29, 28, 11, 1.0), 262143.0);
    wd.setRawValue(std::stol("EFFFFFFF", nullptr, 16));
    EXPECT_DOUBLE_EQ(wd.getBnrValue(false, 29, 28, 11, 1.0), 262143.0);
}

TEST(A429WordTest, isParityValid) {
    // tests with ODD parity
    A429Word wdOdd = A429Word("ABCD2234", true, 16);
    EXPECT_TRUE(wdOdd.isParityValid());
    wdOdd.setParity(false);
    EXPECT_FALSE(wdOdd.isParityValid());
    wdOdd.setRawValue(std::stol("123417CD", nullptr, 16));
    EXPECT_FALSE(wdOdd.isParityValid());
    wdOdd.setParity(true);
    EXPECT_TRUE(wdOdd.isParityValid());
    // tests with EVEN parity
    A429Word wdEven = A429Word("ABCD2234", true, 16, false);
    EXPECT_FALSE(wdEven.isParityValid());
    wdEven.setParity(false);
    EXPECT_TRUE(wdEven.isParityValid());
    wdEven.setRawValue(std::stol("123417CD", nullptr, 16));
    EXPECT_TRUE(wdEven.isParityValid());
    wdEven.setParity(true);
    EXPECT_FALSE(wdEven.isParityValid());
}

TEST(A429WordTest, toggleBit) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    for (int i = 1; i < 33; ++i) {
        wd.toggleBit(i);
        EXPECT_FALSE(wd.getBit(i));
        wd.toggleBit(i);
        EXPECT_TRUE(wd.getBit(i));
    }
    // out_of_range exception
    EXPECT_THROW(wd.toggleBit(33), std::out_of_range);
}