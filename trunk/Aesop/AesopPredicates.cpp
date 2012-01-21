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

   PredicatesInterface & Predicates::create(std::string name)
   {
      mCurPred = Predicate(name);
      return *this;
   }

   PredicatesInterface & Predicates::parameter(std::string name, std::string type)
   {
      mCurPred.mParams.push_back(name);
      mCurPred.mTypes.push_back(type);
      return *this;
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

   GOAPPredicates::GOAPPredicates()
   {
   }

   GOAPPredicates::~GOAPPredicates()
   {
   }

   PredicatesInterface & GOAPPredicates::create(std::string name)
   {
      mCurPred = name;
      return *this;
   }

   PredicatesInterface & GOAPPredicates::parameter(std::string name, std::string type)
   {
      return *this;
   }

   void GOAPPredicates::add()
   {
      // Add new predicate
      mPredicates.insert(mCurPred);
   }

   bool GOAPPredicates::has(std::string name) const
   {
      return mPredicates.find(name) != mPredicates.end();
   }
};
