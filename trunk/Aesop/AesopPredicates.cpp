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

   void Predicates::add(Predicate &newpred)
   {
      // Check for compliance with requirements.
      if(!getRequirements().predicateParameters && newpred.getParams().size())
         return;
      for(unsigned int i = 0; i < newpred.getParams().size(); i++)
      {
         for(Predicate::paramlist::const_iterator it = newpred.getParams().begin(); it != newpred.getParams().end(); it++)
            if(it->second != "")
               return;
         if(!getRequirements().typing && newpred.getParams()[i].second != "")
            return;
         else if(!getTypes().has(newpred.getParams()[i].second))
            return;
      }
      // Add new predicate
      mPredicates[newpred.getName()] = newpred;
   }

   Predicate Predicates::create(std::string name)
   {
      return Predicate(name);
   }

   bool Predicates::has(std::string name) const
   {
      return mPredicates.find(name) != mPredicates.end();
   }
};
