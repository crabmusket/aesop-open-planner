/// @file AesopActionTest.h
/// @brief gtest cases for Action class.

#include "gtest/gtest.h"
#include "Aesop.h"

using namespace Aesop;

/// @brief Test fixture for the Action class.
/// @ingroup AesopTest
class ActionTest : public ::testing::Test {
protected:
   ActionTest()
   {
   }
};

TEST_F(ActionTest, Constructor)
{
   Action ac;
   EXPECT_EQ(ac.getName(), "");
   EXPECT_EQ(ac.getCost(), 1.0f);
   EXPECT_EQ(ac.getNumParams(), 0);
   EXPECT_EQ(ac.begin(), ac.end());
}

TEST_F(ActionTest, Named)
{
   Action ac("test", 2.0f);
   EXPECT_EQ(ac.getName(), "test");
   EXPECT_EQ(ac.getCost(), 2.0f);
   EXPECT_EQ(ac.getNumParams(), 0);
   EXPECT_EQ(ac.begin(), ac.end());
}

TEST_F(ActionTest, Conditions)
{
   Action ac;
   Fact f1(0);
   ac.condition(f1, IsSet, 1);
   ASSERT_NE(ac.begin(), ac.end());
   const Fact &f = ac.begin()->first;
   const Operation &op = ac.begin()->second;
   ASSERT_EQ(f, f1);
   ASSERT_EQ(op.ctype, IsSet);
   ASSERT_EQ(op.cval, 1);
   ASSERT_EQ(op.etype, NoEffect);
}
