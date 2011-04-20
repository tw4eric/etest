#ifndef DEPEND
#ifdef LINUX
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#else
#include <iostream.h>
#endif
#endif
#ifdef USE_GTEST
#include "gtest/gtest.h"
#else
#include "etest.hh"
#endif

int adder(int a, int b) {
    return a + b + 1;
}

TEST(sample, twoEqualsTwo) {
    EXPECT_TRUE(1 == 2) << "(1) One And Two Are Not Equal!";
    ASSERT_TRUE(2 == 2) << "(2) Two and Two are EQUAL!";
}

TEST(sample, threeIsNotSix) {
    EXPECT_TRUE(1 == 2) << "**** (1) One And Two Are Not Equal!";
    EXPECT_TRUE(1 == 4) << "^^^^ (2) One And Two Are Not Equal!";
    ASSERT_TRUE(3 == 6) << "     (3) Three is NOT six!!";
    EXPECT_TRUE(1 == 2) << "     (4) ****One And Two Are Not Equal!";
}

TEST(sample, adderDoesNotWorkRight) {
    ASSERT_TRUE(adder(2, 2) == 4) << "Adder not working as expected!";
}

int main( int argc, char ** argv )
{
#ifdef USE_GTEST
    ::testing::InitGoogleTest(&argc, argv);
#endif
    return RUN_ALL_TESTS();
}
