/// @file AesopPredicates.cpp
/// @brief Implementation of Predicates class as defined in AesopPredicates.h

#include "AesopPredicates.h"

namespace ae {
   /// @class AesopPredicates
   ///
   /// 

   AesopPredicates::AesopPredicates(const Types &types)
      : mTypes(types)
   {
   }

   AesopPredicates::~AesopPredicates()
   {
   }

   AesopPredicates &AesopPredicates::create(pname name)
   {
      mCurPred = Predicate(name);
      return *this;
   }

   AesopPredicates &AesopPredicates::parameter(pparam name, std::string type)
   {
      mCurPred.mParams.push_back(name);
      mCurPred.mTypes.push_back(type);
      return *this;
   }

   void AesopPredicates::add()
   {
      // Add new predicate
      mPredicates[mCurPred.mName] = mCurPred;
   }

   unsigned int AesopPredicates::size() const
   {
      return mPredicates.size();
   }

   /// Predicates is implemented using a std::set, which means some sort of
   /// balanced binary search tree. That means performance something like
   /// O(logn) in the number of predicate names defined. And remember that each
   /// of those operations is a string comparison.
   bool AesopPredicates::has(pname name) const
   {
      return mPredicates.find(name) != mPredicates.end();
   }

   bool AesopPredicates::hasParam(pname name, pparam param) const
   {
      return false;
   }
   
   /// @class GOAPPredicates
   ///
   /// 

   GOAPPredicates::GOAPPredicates()
   {
      mPredicateMax = 0;
   }

   GOAPPredicates::~GOAPPredicates()
   {
   }

   unsigned int GOAPPredicates::size() const
   {
      return mPredicateMax + 1;
   }

   void GOAPPredicates::size(unsigned int count)
   {
      mPredicateMax = count;
   }

   /// GOAPPredicates is just an array of flags, so the performance of this
   /// method should be pretty much O(1).
   bool GOAPPredicates::has(pname id) const
   {
      return id <= mPredicateMax;
   }

   bool GOAPPredicates::hasParam(pname id, pparam param) const
   {
      return false;
   }
};
