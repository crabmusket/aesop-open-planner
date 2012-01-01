/// @file AesopPredicates.cpp
/// @brief Implementation of Predicatess class as defined in AesopPredicates.h

#include "AesopPredicates.h"

namespace ae {
   /// @class Predicates
   ///
   /// 

   Predicates::Predicates(const Requirements &reqs, const Types &types)
      : mRequirements(reqs), mTypes(types)
   {
   }

   Predicates::~Predicates()
   {
   }

   void Predicates::add(Predicates::Predicate &newpred)
   {
      // Check for compliance with requirements.
      if(!getRequirements().predicateParameters && newpred.getNumParams())
         return;
      if(!getRequirements().typing)
      {
         for(unsigned int i = 0; i < newpred.getNumParams(); i++)
            if(newpred.params[i].second != "")
               return;
      }
      mPredicates[newpred.name] = newpred;
   }

   Predicates::Predicate Predicates::create(std::string name)
   {
      return Predicate(name);
   }

   bool Predicates::has(std::string name) const
   {
      return mPredicates.find(name) != mPredicates.end();
   }
};
