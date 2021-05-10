#include <gtest/gtest.h>
#include "../a429word.hpp"

TEST(A429WordTest, DefaultConstructorTest) {
    A429Word wd = A429Word();
    EXPECT_TRUE(wd.getLabelAsOctalString() == "000") << "get: " << wd.getLabelAsOctalString() << " instead of 000";
    EXPECT_EQ(wd.getBnrValue(true, 29, 28, 11, 1.0), 0.0);
    for (int i=1; i<33; ++i) {
        EXPECT_FALSE(wd.getBit(i));
    }

}

TEST(A429WordTest, IntegerConstructorTest) {
    A429Word wd = A429Word(4294967295, true);
    EXPECT_TRUE(wd.getLabelAsOctalString() == "377") << "get: " << wd.getLabelAsOctalString() << " instead of 377";
    EXPECT_EQ(wd.getBnrValue(true, 29, 28, 11, 1.0),  0.0);
    for (int i=1; i<33; ++i) {
        EXPECT_TRUE(wd.getBit(i));
    }
}

TEST(A429WordTest, StringConstructorTest) {
    A429Word wd = A429Word("FFFFFFFF", true, 16);
    EXPECT_TRUE(wd.getLabelAsOctalString() == "377") << "get: " << wd.getLabelAsOctalString() << " instead of 377";
    EXPECT_EQ(wd.getBnrValue(true, 29, 28, 11, 1.0),  0.0);
    for (int i=1; i<33; ++i) {
        EXPECT_TRUE(wd.getBit(i));
    }
}