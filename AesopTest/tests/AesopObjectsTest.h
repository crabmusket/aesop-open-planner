/// @file AesopObjectsTest.h
/// @brief gtest cases for Objects class.

#include "gtest/gtest.h"
#include "AesopObjects.h"
#include "AesopTypes.h"

using namespace ae;

/// @brief Test fixture for the Objects class.
/// @ingroup AesopTest
class ObjectsTest : public ::testing::Test {
protected:
   Objects objs;
   Types types;

   ObjectsTest()
   {
   }
};

TEST_F(ObjectsTest, Constructor)
{
   EXPECT_EQ(objs.size(), 0);
}

TEST_F(ObjectsTest, TypedConstructor)
{
   Objects tobjs(types);
   EXPECT_EQ(tobjs.size(), 0);
}

TEST_F(ObjectsTest, Add)
{
   objs.add("a");
   EXPECT_EQ(objs.size(), 1);
   objs.add("b", "object");
   EXPECT_EQ(objs.size(), 1);
   objs.add("c", "");
   EXPECT_EQ(objs.size(), 2);
}

TEST_F(ObjectsTest, TypedAdd)
{
   types.add("object");
   Objects tobjs(types);
   tobjs.add("a");
   EXPECT_EQ(tobjs.size(), 1);
   tobjs.add("b", "tool");
   EXPECT_EQ(tobjs.size(), 1);
   tobjs.add("c", "object");
   EXPECT_EQ(tobjs.size(), 2);
}

TEST_F(ObjectsTest, TypedSizing)
{
   /// Create a simple type hierarchy.
   types.add("object");
   types.add("place");
   types.add("book", "object");
   Objects tobjs(types);
   tobjs.add("Aziraphale");
   tobjs.add("Lisbon", "place");
   tobjs.add("table", "object");
   tobjs.add("Smiley's People", "book");

   EXPECT_EQ(tobjs.size(), 4);
   EXPECT_EQ(tobjs.size(""), 4);
   EXPECT_EQ(tobjs.size("object"), 2);
   EXPECT_EQ(tobjs.size("book"), 1);
}
