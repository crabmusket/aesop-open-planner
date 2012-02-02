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

   /// Predicates is implemented using a std::set, which means some sort of
   /// balanced binary search tree. That means performance something like
   /// O(logn) in the number of predicate names defined. And remember that each
   /// of those operations is a string comparison.
   bool AesopPredicates::has(pname name) const
   {
      return mPredicates.find(name) != mPredicates.end();
   }
   
   /// @class GOAPPredicates
   ///
   /// 

   GOAPPredicates::GOAPPredicates()
   {
   }

   GOAPPredicates::~GOAPPredicates()
   {
   }

   void GOAPPredicates::reserve(unsigned int count)
   {
      mPredicates.reserve(count);
   }

   void GOAPPredicates::add(pname id)
   {
      if(mPredicates.size() <= id)
         mPredicates.resize(id + 1);
      mPredicates[id] = true;
   }

   /// GOAPPredicates is just an array of flags, so the performance of this
   /// method should be pretty much O(1).
   bool GOAPPredicates::has(pname id) const
   {
      return id < mPredicates.size() && mPredicates[id];
   }
};
