/// @file AesopActionSet.cpp
/// @brief Implementation of ActionSet class as defined in AesopActionSet.h

#include "AesopActionSet.h"

namespace ae {
   /// @class ActionSet
   ///
   /// 

   ActionSet::ActionSet(const Predicates &preds)
      : mPredicates(preds)
   {
   }

   ActionSet::~ActionSet()
   {
   }

   Action ActionSet::create(std::string name)
   {
      return Action(name);
   }

   void ActionSet::add(Action &newac)
   {
      mActions[newac.getName()] = newac;
   }

   bool ActionSet::has(std::string name) const
   {
      return mActions.find(name) != mActions.end();
   }
};
