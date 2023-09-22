#include <gtest/gtest.h>
#include "polynom.h"

TEST(testPolynomial, simpleArr)
{
    int ans = point<6, 1, 1, 0>::func;
    EXPECT_EQ(ans, 42);
}

TEST(testPolynomial, negativePoint)
{
    int ans = point<-3, 4, 3, 2, 1>::func;
    EXPECT_EQ(ans, -86);
}

TEST(testPolynomial, zeroCoefs)
{
    int ans = point<4, 0, 1, 2, 0>::func;
    EXPECT_EQ(ans, 24);
}

TEST(testPolynomial, largeArr)
{
    int ans = point<2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1>::func;
    EXPECT_EQ(ans, 2047);
}

TEST(testOutput, simpleArr)
{
    std::stringstream ans;
    ans << point<6, 1, 1, 0>();
    EXPECT_EQ(ans.str(), "(x ^ 2) + (x ^ 1) + 0\n");
}

TEST(testOutput, negativePoint)
{
    std::stringstream ans;
    ans << point<-3, 4, 3, 2, 1>();
    EXPECT_EQ(ans.str(), "4 * (x ^ 3) + 3 * (x ^ 2) + 2 * (x ^ 1) + 1\n");
}

TEST(testOutput, zeroCoefs)
{
    std::stringstream ans;
    ans << point<4, 0, 1, 2, 0>();
    EXPECT_EQ(ans.str(), "(x ^ 2) + 2 * (x ^ 1) + 0\n");
}

TEST(testOutput, largeArr)
{
    std::stringstream ans;
    ans << point<2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1>();
    EXPECT_EQ(ans.str(), "(x ^ 10) + (x ^ 9) + (x ^ 8) + (x ^ 7) + (x ^ 6) + (x ^ 5) + (x ^ 4) + (x ^ 3) + (x ^ 2) + (x ^ 1) + 1\n");
}
