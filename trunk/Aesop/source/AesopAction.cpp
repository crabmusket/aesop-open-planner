/// @file AesopAction.cpp
/// @brief Implementation of Action class as defined in Aesop.h

#include "Aesop.h"

namespace ae {
   /// @class Action
   ///
   /// Based on the STRIPS concept of an action, an Action represents an atomic
   /// change we can make to the world, and is the building block of all plans
   /// made with Aesop.
   /// An Action is essentially a change to the world state. To perform an
   /// Action, the world must be in a certain state. After the Action is
   /// performed, certain changes will be made to that world state.

   Action::Action(std::string name, float cost)
   {
      mName = name;
      if(cost < 0.0f)
         cost = 0.0f;
      mCost = cost;
      mNumParams = 0;
   }

   Action::~Action()
   {
   }

   void Action::addCondition(PName name, PVal val)
   {
      mCondition[name] = val;
   }

   void Action::addEffect(PName name, PVal val)
   {
      mEffect[name] = val;
   }

   void Action::addConditionParam(PName name, unsigned int param)
   {
      if(param < mNumParams)
         mConditionParam[name] = param;
   }

   void Action::addEffectParam(PName name, unsigned int param)
   {
      if(param < mNumParams)
         mEffectParam[name] = param;
   }
};
