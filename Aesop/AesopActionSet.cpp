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

   ActionSet::Action ActionSet::create(std::string name)
   {
      return Action(name);
   }

   void ActionSet::add(ActionSet::Action &newac)
   {
      // Check for compliance with requirements.
      if(getRequirements().maxActionParams >= 0 && (int)newac.getNumParams() > getRequirements().maxActionParams)
         return;
      if(!getRequirements().typing)
      {
         for(unsigned int i = 0; i < newac.getNumParams(); i++)
            if(newac.params[i].second != "")
               return;
      }
      mActions[newac.name] = newac;
   }

   bool ActionSet::has(std::string name) const
   {
      return mActions.find(name) != mActions.end();
   }
};
