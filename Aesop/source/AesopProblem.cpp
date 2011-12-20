/// @file AesopProblem.cpp
/// @brief Implementation of Problem class defined in Aesop.h

#include "Aesop.h"

namespace ae {
   /// @class Problem
   ///
   /// Problem represents a particular problem instance within some Domain.

   Problem::Problem(const Domain &d)
   {
      mDomain = &d;
   }

   Problem::~Problem()
   {
   }

   void Problem::addObject(const char *name, const char *type)
   {
      if(mDomain->hasType(type))
         mObjects[type].insert(name);
   }
};