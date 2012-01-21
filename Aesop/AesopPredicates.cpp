/// @file AesopPredicates.cpp
/// @brief Implementation of Predicates class as defined in AesopPredicates.h

#include "AesopPredicates.h"

namespace ae {
   /// @class Predicates
   ///
   /// 

   Predicates::Predicates(const Types &types)
      : mTypes(types)
   {
   }

   Predicates::~Predicates()
   {
   }

   void Predicates::create(std::string name)
   {
      mCurPred = Predicate(name);
   }

   void Predicates::parameter(std::string name, std::string type)
   {
      mCurPred.mParams.push_back(name);
      mCurPred.mTypes.push_back(type);
   }

   void Predicates::add()
   {
      // Add new predicate
      mPredicates[mCurPred.mName] = mCurPred;
   }

   bool Predicates::has(std::string name) const
   {
      return mPredicates.find(name) != mPredicates.end();
   }
};
