/// @file AesopTypesTest.h
/// gtest cases for Types class.

#include "gtest/gtest.h"
#include "AesopTypes.h"

using namespace Aesop;

/// Test fixture for the Types class.
/// @ingroup AesopTest
class TypesTest : public ::testing::Test {
protected:
   Types types;

   TypesTest()
   {
   }
};

TEST_F(TypesTest, Constructor)
{
   EXPECT_EQ(types.size(), 0);
   // Check for null type.
   EXPECT_TRUE(types.has(""));
   // Check for another type that has not been added.
   EXPECT_FALSE(types.has("object"));
}

TEST_F(TypesTest, Add)
{
   // Simplest case of adding a type.
   types.add("object");
   EXPECT_TRUE(types.has("object"));

   // Adding a type with a nonexistent parent should fail.
   types.add("child", "parent");
   EXPECT_FALSE(types.has("child"));
}

TEST_F(TypesTest, IsOf)
{
   // Null case for type hierarchy.
   EXPECT_TRUE(types.isOf("", ""));
   // Using an undefined type.
   EXPECT_FALSE(types.isOf("object", ""));

   types.add("object");
   // Should have defaulted to being a child of "".
   EXPECT_TRUE(types.isOf("object", ""));

   types.add("child", "object");
   // Check ancestry.
   EXPECT_TRUE(types.isOf("child", "object"));
   EXPECT_TRUE(types.isOf("child", ""));
}

TEST_F(TypesTest, NoTypes)
{
   EXPECT_EQ(NoTypes.size(), 0);
   EXPECT_TRUE(NoTypes.has(""));
   EXPECT_FALSE(NoTypes.has("object"));
}
