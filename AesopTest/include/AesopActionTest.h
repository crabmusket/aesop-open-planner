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
   EXPECT_TRUE(ac.getRequired().empty());
   EXPECT_TRUE(ac.getSet().empty());
   EXPECT_TRUE(ac.getCleared().empty());
   EXPECT_TRUE(ac.getRequiredParams().empty());
   EXPECT_TRUE(ac.getSetParams().empty());
}

TEST_F(ActionTest, RequiredPredicates)
{
   // Add a single predicate, check for correctness.
   ac.addRequired(pn1, pfalse);
   EXPECT_FALSE(ac.getRequired().empty());
   EXPECT_EQ(ac.getRequired().at(pn1), pfalse);
   // Overwrite predicate, check for correctness.
   ac.addRequired(pn1, ptrue);
   EXPECT_EQ(ac.getRequired().size(), 1);
   EXPECT_EQ(ac.getRequired().at(pn1), ptrue);
   // Add a new predicate and check for correctness.
   ac.addRequired(pn2, ptrue);
   EXPECT_EQ(ac.getRequired().size(), 2);
   EXPECT_EQ(ac.getRequired().at(pn2), ptrue);
}

TEST_F(ActionTest, EffectPredicates)
{
   // Add a single predicate, check for correctness.
   ac.addSet(pn1, pfalse);
   EXPECT_FALSE(ac.getSet().empty());
   EXPECT_EQ(ac.getSet().at(pn1), pfalse);
   // Overwrite predicate, check for correctness.
   ac.addSet(pn1, ptrue);
   EXPECT_EQ(ac.getSet().size(), 1);
   EXPECT_EQ(ac.getSet().at(pn1), ptrue);
   // Add a new predicate and check for correctness.
   ac.addSet(pn2, ptrue);
   EXPECT_EQ(ac.getSet().size(), 2);
   EXPECT_EQ(ac.getSet().at(pn2), ptrue);
   // Add a PName to clear.
   ac.addClear(pn1);
   EXPECT_EQ(ac.getCleared().size(), 1);
   // Add the same entry; it should be rejected.
   ac.addClear(pn1);
   EXPECT_EQ(ac.getCleared().size(), 1);
   // Add a new entry; the cleared list should grow.
   ac.addClear(pn2);
   EXPECT_EQ(ac.getCleared().size(), 2);
}
