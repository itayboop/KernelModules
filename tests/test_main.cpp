#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(SimpleTest, TestAddition)
{
    EXPECT_EQ(2, 1 + 1);
}

TEST(SimpleTest, TestNotEqual)
{
    EXPECT_NE(3, 1 + 1);
}
