/// @file AesopProblem.cpp
/// @brief Implementation of Problem class from AesopProblem.h

#include "AesopProblem.h"
#include <algorithm>

namespace Aesop {
   Problem::Problem()
   {
      goal = NULL;
      success = false;
      lastID = 0;
   }

   Problem::~Problem()
   {
   }
};
