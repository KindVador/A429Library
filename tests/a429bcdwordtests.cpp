#include <gtest/gtest.h>
#include "../a429bcdword.hpp"

TEST(A429BcdWordTest, DefaultConstructorTest) {
    A429BcdWord wd = A429BcdWord();
    EXPECT_EQ(wd.getLabelAsOctalString(), "000") << "getLabelAsOctalString() returned " << wd.getLabelAsOctalString() << " instead of 000";
    for (int i=1; i<33; ++i) {
        EXPECT_FALSE(wd.getBit(i)) << "getBit(" << i << ") returned "  << wd.getBit(i) << " instead of 0";
    }
    EXPECT_DOUBLE_EQ(wd.getBnrValue(true, 29, 28, 11, 1.0), 0.0);
    EXPECT_EQ(wd.getLabelAsBinaryString(true), "00000000") << "getLabelAsBinaryString(true) returned " << wd.getLabelAsBinaryString(true) << " instead of 00000000";
}

TEST(A429BcdWordTest, Format0) {
    /*
    Format 0 description:
        SSM = 00 (Plus, North, East, Right, To, Above), 11 (Minus, South, West, Left, From, Below), 01 (No Computed Data), 10 (Functional Test)
        Digit 1 = bit 29
        Digit 2 = bits 28/25
        Digit 3 = bits 24/21
        Digit 4 = bits 20/17
        Digit 5 = bits 16/13
        Digit 6 = bits 12/09
    */
   // LABEL=245 BCD_value=123456 SSM=00  Parity=0(Valid)
    
    DigitsVec digitsPos = {std::make_pair(29, 29), std::make_pair(28, 25), std::make_pair(24, 21), std::make_pair(20, 17), std::make_pair(16, 13), std::make_pair(12, 9)};
    A429BcdWord wd1 = A429BcdWord("123456A5", digitsPos, true, 16, true, 1.0);
    EXPECT_EQ(wd1.getLabelAsOctalString(), "245");
    EXPECT_EQ(wd1.sdi(), 2);
    EXPECT_EQ(wd1.ssm(), 0);
    EXPECT_EQ(wd1.parity(), 0);
    EXPECT_NEAR(123456, wd1.value(), 0.001);
    // same raw with a new resolution
    wd1.setResolution(0.1);
    EXPECT_NEAR(12345.6, wd1.value(), 0.001);
}

TEST(A429BcdWordTest, Format1) {
    /*
    Format 1 description:
        SSM = 00 (Plus, North, East, Right, To, Above), 11 (Minus, South, West, Left, From, Below), 01 (No Computed Data), 10 (Functional Test)
        Digit 1 = bits 26/23
        Digit 2 = bits 22/19
        Digit 3 = bits 18/15
        Digit 4 = bits 14/11
        SDI = bits 10/09
    */
    DigitsVec digitsPos = {std::make_pair(26, 23), std::make_pair(22, 19), std::make_pair(18, 15), std::make_pair(14, 11)};
    A429BcdWord wd1 = A429BcdWord("6048D2E9", digitsPos, true, 16, true, 1.0);
    EXPECT_EQ(wd1.getLabelAsOctalString(), "227");
    EXPECT_EQ(wd1.sdi(), 2);
    EXPECT_EQ(wd1.ssm(), 3);
    EXPECT_EQ(wd1.parity(), 0);
    EXPECT_NEAR(1234, wd1.value(), 0.001);
    // same raw with a new resolution
    wd1.setResolution(0.1);
    EXPECT_NEAR(123.4, wd1.value(), 0.001);
}

TEST(A429BcdWordTest, Format2) {
    /*
    Format 2/3 description:
        SSM = 00 (Plus, North, East, Right, To, Above), 11 (Minus, South, West, Left, From, Below), 01 (No Computed Data), 10 (Functional Test)
        Digit 1 = bits 29/27
        Digit 2 = bits 26/23
        Digit 3 = bits 22/19
        Digit 4 = bits 18/15
        Digit 5 = bits 14/11
        SDI = bits 10/09
    */
    DigitsVec digitsPos = {std::make_pair(29, 27), std::make_pair(26, 23), std::make_pair(22, 19), std::make_pair(18, 15), std::make_pair(14, 11)};
    A429BcdWord wd1 = A429BcdWord("DD950D69", digitsPos, true, 16, true, 1.0);
    EXPECT_EQ(wd1.getLabelAsOctalString(), "226");
    EXPECT_EQ(wd1.sdi(), 1);
    EXPECT_EQ(wd1.ssm(), 2);
    EXPECT_EQ(wd1.parity(), 1);
    EXPECT_NEAR(76543, wd1.value(), 0.001);
    // same raw with a new resolution
    wd1.setResolution(0.1);
    EXPECT_NEAR(7654.3, wd1.value(), 0.001);
    
}

TEST(A429BcdWordTest, Format6) {
    /*
    Format 6 description (use to encode a frequency):
        SSM = 00 (Plus, North, East, Right, To, Above), 11 (Minus, South, West, Left, From, Below), 01 (No Computed Data), 10 (Functional Test)
        Digit 1 = bits 29/27
        Digit 2 = bits 26/23
        Digit 3 = bits 22/19
        Digit 4 = bits 18/15
        data = bit 14
        SDI = bits 10/09
    */
    DigitsVec digitsPos = {std::make_pair(29, 27), std::make_pair(26, 23), std::make_pair(22, 19), std::make_pair(18, 15)};
    A429BcdWord wd1 = A429BcdWord("5D950DA1", digitsPos, true, 16, true, 1.0);
    EXPECT_EQ(wd1.getLabelAsOctalString(), "205");
    EXPECT_EQ(wd1.sdi(), 1);
    EXPECT_EQ(wd1.ssm(), 2);
    EXPECT_EQ(wd1.parity(), 0);
    EXPECT_NEAR(7654, wd1.value(), 0.001);
    // same raw with a new resolution
    wd1.setResolution(0.1);
    EXPECT_NEAR(765.4, wd1.value(), 0.001);
    
}

TEST(A429BcdWordTest, Format7) {
    /*
    Format 7 description:
        SSM = 00 (Plus, North, East, Right, To, Above), 11 (Minus, South, West, Left, From, Below), 01 (No Computed Data), 10 (Functional Test)
        Digit 1 = bits 27/26
        Digit 2 = bits 25/22
        Digit 3 = bits 21/18
        Digit 4 = bits 17/14
        SDI = bits 10/09
    */
    DigitsVec digitsPos = {std::make_pair(27, 26), std::make_pair(25, 22), std::make_pair(21, 18), std::make_pair(17, 14)};
    A429BcdWord wd1 = A429BcdWord("824683E0", digitsPos, true, 16, true, 1.0);
    EXPECT_EQ(wd1.getLabelAsOctalString(), "007");
    EXPECT_EQ(wd1.sdi(), 3);
    EXPECT_EQ(wd1.ssm(), 0);
    EXPECT_EQ(wd1.parity(), 1);
    EXPECT_NEAR(1234, wd1.value(), 0.001);
    // same raw with a new resolution
    wd1.setResolution(0.1);
    EXPECT_NEAR(123.4, wd1.value(), 0.001);
    
}

TEST(A429BcdWordTest, Format8) {
    /*
    Format 8 description (use to encode DME frequency):
        SSM = 00 (Plus, North, East, Right, To, Above), 11 (Minus, South, West, Left, From, Below), 01 (No Computed Data), 10 (Functional Test)
        Digit 1 = always 1 (not encoded in the word)
        Digit 2 = bits 28/26
        Digit 3 = bits 25/22
        Digit 4 = bits 21/18
        Digit 5 = bits 17/14
        SDI = bits 10/09
    */
    DigitsVec digitsPos = {std::make_pair(28, 26), std::make_pair(25, 22), std::make_pair(21, 18), std::make_pair(17, 14)};
    A429BcdWord wd1 = A429BcdWord("8468A0CA", digitsPos, true, 16, true, 1.0);
    EXPECT_EQ(wd1.getLabelAsOctalString(), "123");
    EXPECT_EQ(wd1.sdi(), 0);
    EXPECT_EQ(wd1.ssm(), 0);
    EXPECT_EQ(wd1.parity(), 1);
    EXPECT_NEAR(2345, wd1.value(), 0.001);
    // same raw with a new resolution
    wd1.setResolution(0.01);
    EXPECT_NEAR(23.45, wd1.value(), 0.001);
    
}

TEST(A429BcdWordTest, Format9) {
    /*
    Format 9 description:
        SSM = 00 (Plus, North, East, Right, To, Above), 11 (Minus, South, West, Left, From, Below), 01 (No Computed Data), 10 (Functional Test)
        Digit 1 = bit 23
        Digit 2 = bits 22/19
        Digit 3 = bits 18/15
        Digit 4 = bits 14/11

        SDI = bits 10/09
    */
    DigitsVec digitsPos = {std::make_pair(23, 23), std::make_pair(22, 19), std::make_pair(18, 15), std::make_pair(14, 11)};
    A429BcdWord wd1 = A429BcdWord("0048D0B8", digitsPos, true, 16, true, 1.0);
    EXPECT_EQ(wd1.getLabelAsOctalString(), "035");
    EXPECT_EQ(wd1.sdi(), 0);
    EXPECT_EQ(wd1.ssm(), 0);
    EXPECT_EQ(wd1.parity(), 0);
    EXPECT_NEAR(1234, wd1.value(), 0.001);
    // same raw with a new resolution
    wd1.setResolution(0.1);
    EXPECT_NEAR(123.4, wd1.value(), 0.001);
    
}