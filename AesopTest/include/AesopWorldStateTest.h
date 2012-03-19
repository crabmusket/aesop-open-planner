/// @file AesopWorldStateTest.h
/// @brief gtest cases for WorldState class.

#include "gtest/gtest.h"
#include "Aesop.h"

/// @brief Test fixture for the WorldState class.
/// @ingroup AesopTest
class WorldStateTest : public ::testing::Test {
protected:

   WorldStateTest()
   {
   }
};

TEST_F(WorldStateTest, Constructor)
{
}

TEST_F(WorldStateTest, Predicates)
{
   WorldState s1;
   PName p1 = 3;
   PVal v1 = 'A';
   PVal v2 = 'B';
   PVal v;
   s1.set(Fact(p1) % 0 % 1, v1);
   s1.set(Fact(p1) % 1 % 1, v2);
   EXPECT_TRUE(s1.get(Fact(p1) % 0 % 1, v));
   EXPECT_EQ(v, v1);
   EXPECT_TRUE(s1.get(Fact(p1) % 1 % 1, v));
   EXPECT_EQ(v, v2);
}

TEST_F(WorldStateTest, PreMatch)
{
}

TEST_F(WorldStateTest, PostMatch)
{
}

TEST_F(WorldStateTest, ApplyForward)
{
}

TEST_F(WorldStateTest, ApplyReverse)
{
}
