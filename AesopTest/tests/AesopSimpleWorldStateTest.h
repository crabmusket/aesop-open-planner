/// @file AesopWorldStateTest.h
/// gtest cases for WorldState class.

#include "gtest/gtest.h"
#include "AesopWorldState.h"

using namespace Aesop;

/// Test fixture for the WorldState class.
/// @ingroup AesopTest
class SimpleWorldStateTest : public ::testing::Test {
protected:
   SimpleWorldState ws1;
   SimpleWorldState ws2;

   WorldStateTest()
      :pn1("pred1"),
      pn2("pred2"),
      ptrue(1),
      pfalse(0)
   {
   }
};

TEST_F(WorldStateTest, Predicates)
{
   // Assign a value to a predicate.
   ws1.setPredicate(pn1, ptrue);
   EXPECT_TRUE(ws1.predicateSet(pn1));
   EXPECT_EQ(ws1.getPredicate(pn1), ptrue);
   // Overwrite the value of a predicate.
   ws1.setPredicate(pn1, pfalse);
   EXPECT_TRUE(ws1.predicateSet(pn1));
   EXPECT_EQ(ws1.getPredicate(pn1), pfalse);
   // Test a second predicate. Ensure previous values untouched.
   ws1.setPredicate(pn2, ptrue);
   EXPECT_TRUE(ws1.predicateSet(pn2));
   EXPECT_EQ(ws1.getPredicate(pn2), ptrue);
   EXPECT_TRUE(ws1.predicateSet(pn1));
   EXPECT_EQ(ws1.getPredicate(pn1), pfalse);
   // Unset one predicate.
   ws1.unsetPredicate(pn1);
   EXPECT_FALSE(ws1.predicateSet(pn1));
   EXPECT_EQ(ws1.getPredicate(pn1), 0);
   EXPECT_TRUE(ws1.predicateSet(pn2));
   EXPECT_EQ(ws1.getPredicate(pn2), ptrue);
}

TEST_F(WorldStateTest, Comparison)
{
   // By default WorldStates should be equal with no predicates set.
   EXPECT_EQ(WorldState::comp(ws1, ws2), 0);
   // A predicate set in one but not the other is a difference.
   ws1.setPredicate(pn1, ptrue);
   EXPECT_EQ(WorldState::comp(ws1, ws2), 1);
   // A predicate set to different values is a difference.
   ws2.setPredicate(pn1, pfalse);
   EXPECT_EQ(WorldState::comp(ws1, ws2), 1);
   // Introduce a second predicate.
   ws2.setPredicate(pn2, pfalse);
   EXPECT_EQ(WorldState::comp(ws1, ws2), 2);
}

TEST_F(WorldStateTest, Equality)
{
   // By default WorldStates should be equal.
   EXPECT_TRUE(ws1 == ws2);
   // Introduce a predicate to one that makes them no longer equal.
   ws1.setPredicate(pn1, ptrue);
   EXPECT_FALSE(ws1 == ws2);
   // Restore equality in the other.
   ws2.setPredicate(pn1, ptrue);
   EXPECT_TRUE(ws1 == ws2);
   // Test !=, but its correctness should follow the correctness of ==.
   EXPECT_FALSE(ws1 != ws2);
}
