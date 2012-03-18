/// @file AesopActionTest.h
/// @brief gtest cases for Action class.

#include "gtest/gtest.h"
#include "Aesop.h"

using namespace Aesop;

/// @brief Test fixture for the Fact struct.
/// @ingroup AesopTest
class FactTest : public ::testing::Test {
protected:
   FactTest()
   {
   }
};

/*
TEST_F(FactTest, )
{
   
}
*/

TEST_F(FactTest, Constructor)
{
   PName pred = 3;
   Fact f1(pred);
   EXPECT_EQ(f1.name, pred);
   EXPECT_EQ(f1.params.size(), 0);

   Fact f2(pred, 2);
   EXPECT_EQ(f2.name, pred);
   EXPECT_EQ(f2.params.size(), 2);
}

TEST_F(FactTest, Assignment)
{
   PName pred = 3;
   Fact *f1 = new Fact(pred, 2);
   ASSERT_TRUE(f1 != NULL);
   delete f1;
}

TEST_F(FactTest, Parameters)
{
   // Create a predicate name and some objects.
   PName pred = 4;
   Object o1 = 10, o2 = 3;
   // Create a Fact with 2 parameters containing our objects.
   Fact f1 = Fact(pred) % o1 % o2;
   ASSERT_EQ(f1.params.size(), 2);
   EXPECT_EQ(f1.params[0], o1);
   EXPECT_EQ(f1.params[1], o2);
}

TEST_F(FactTest, Comparison)
{
   Fact f1 = Fact(3) % 0 % 1;
   Fact f2 = Fact(3) % 1 % 1;
   Fact f3 = Fact(4) % 0 % 1;
   EXPECT_FALSE(f1 == f2);
   EXPECT_FALSE(f2 == f3);
   EXPECT_FALSE(f3 == f1);
}
