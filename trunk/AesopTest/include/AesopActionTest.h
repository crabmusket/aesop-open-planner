/// @file AesopActionTest.h
/// @brief gtest cases for Action class.

#include "gtest/gtest.h"
#include "Aesop.h"

using namespace ae;

/// @brief Test fixture for the Action class.
/// @ingroup AesopTest
class ActionTest : public ::testing::Test {
protected:
   Action ac;
   PName pn1;
   PName pn2;
   PVal pfalse;
   PVal ptrue;
   worldrep::const_iterator it;

   ActionTest()
      :ac("action", 1.0f),
      pn1("pred1"),
      pn2("pred2"),
      pfalse(0),
      ptrue(1)
   {
   }
};

TEST_F(ActionTest, Constructor)
{
   // Name and cost should be as specified.
   EXPECT_EQ(ac.getName(), std::string("action"));
   EXPECT_EQ(ac.getCost(), 1.0f);
   // 0 parameters by default.
   EXPECT_EQ(ac.getNumParams(), 0);
   // All lists should be empty.
   EXPECT_TRUE(ac.getConditions().empty());
   EXPECT_TRUE(ac.getEffects().empty());
   EXPECT_TRUE(ac.getConditionParams().empty());
   EXPECT_TRUE(ac.getEffectParams().empty());
}

TEST_F(ActionTest, Conditions)
{
   // Add a single predicate, check for correctness.
   ac.addCondition(pn1, pfalse);
   EXPECT_FALSE(ac.getConditions().empty());
   it = ac.getConditions().find(pn1);
   ASSERT_NE(it, ac.getConditions().end());
   EXPECT_EQ(it->second, pfalse);
   // Overwrite predicate, check for correctness.
   ac.addCondition(pn1, ptrue);
   EXPECT_EQ(ac.getConditions().size(), 1);
   it = ac.getConditions().find(pn1);
   ASSERT_NE(it, ac.getConditions().end());
   EXPECT_EQ(it->second, ptrue);
   // Add a new predicate and check for correctness.
   ac.addCondition(pn2, ptrue);
   EXPECT_EQ(ac.getConditions().size(), 2);
   it = ac.getConditions().find(pn2);
   ASSERT_NE(it, ac.getConditions().end());
   EXPECT_EQ(it->second, ptrue);
}

TEST_F(ActionTest, Effects)
{
   // Add a single predicate, check for correctness.
   ac.addEffect(pn1, pfalse);
   EXPECT_FALSE(ac.getEffects().empty());
   it = ac.getEffects().find(pn1);
   ASSERT_NE(it, ac.getEffects().end());
   EXPECT_EQ(it->second, pfalse);
   // Overwrite predicate, check for correctness.
   ac.addEffect(pn1, ptrue);
   EXPECT_EQ(ac.getEffects().size(), 1);
   it = ac.getEffects().find(pn1);
   ASSERT_NE(it, ac.getEffects().end());
   EXPECT_EQ(it->second, ptrue);
   // Add a new predicate and check for correctness.
   ac.addEffect(pn2, ptrue);
   EXPECT_EQ(ac.getEffects().size(), 2);
   it = ac.getEffects().find(pn2);
   ASSERT_NE(it, ac.getEffects().end());
   EXPECT_EQ(it->second, ptrue);
}
