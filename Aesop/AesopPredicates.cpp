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

   Predicates &Predicates::create(std::string name)
   {
      mCurPred = Predicate(name);
      return *this;
   }

   Predicates &Predicates::parameter(std::string name, std::string type)
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

   /// Predicates is implemented using a std::set, which means some sort of
   /// balanced binary search tree. That means performance something like
   /// O(logn) in the number of predicate names defined. And remember that each
   /// of those operations is a string comparison.
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

   void GOAPPredicates::reserve(unsigned int count)
   {
      mPredicates.reserve(count);
   }

   void GOAPPredicates::add(unsigned int id)
   {
      if(mPredicates.size() <= id)
         mPredicates.resize(id + 1);
      mPredicates[id] = true;
   }

   /// GOAPPredicates is just an array of flags, so the performance of this
   /// method should be pretty much O(1).
   bool GOAPPredicates::has(unsigned int id) const
   {
      return id < mPredicates.size() && mPredicates[id];
   }
};
