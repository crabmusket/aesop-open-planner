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
   EXPECT_EQ(f1.args.size(), 0);
   EXPECT_EQ(f1.indices.size(), 0);
}

TEST_F(FactTest, Arguments)
{
   // Create a predicate name and some objects.
   PName pred = 4;
   Object o1 = 10, o2 = 3;
   // Create a Fact with 2 arguments containing the above objects.
   Fact f1 = Fact(pred) % o1 % o2;
   ASSERT_EQ(f1.args.size(), 2);
   EXPECT_EQ(f1.args[0], o1);
   EXPECT_EQ(f1.args[1], o2);
}

TEST_F(FactTest, Parameters)
{
   // Create a predicate name.
   PName pred = 3;
   // Create a Fact with 2 parameters pointing to arguments 0 and 1.
   Fact f1 = Fact(pred) % Parameter(0) % Parameter(1);
   ASSERT_EQ(f1.indices.size(), 2);
   EXPECT_EQ(f1.indices[0], 0);
   EXPECT_EQ(f1.indices[1], 1);
}

TEST_F(FactTest, MixedConstruction)
{
   // Create a predicate name and an object.
   PName pred = 3;
   Object obj = 5;
   // Create a Fact with one fixed argument and one parameter pointing to argument 3.
   Fact f1 = Fact(pred) % obj % Parameter(3);
   ASSERT_EQ(f1.args.size(), 2);
   ASSERT_EQ(f1.indices.size(), 2);
   EXPECT_EQ(f1.indices[0], -1);
   EXPECT_EQ(f1.indices[1], 3);
   EXPECT_EQ(f1.args[0], obj);
   EXPECT_EQ(f1.args[1], NullObject);
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
