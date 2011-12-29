/// @file AesopTest.cpp
/// @brief Main file of AesopTest module.

#include "gtest/gtest.h"
#include "AesopTest.h"

// Test cases for each class.
#include "tests/AesopActionTest.h"
#include "tests/AesopWorldStateTest.h"
#include "tests/AesopPlannerTest.h"

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
