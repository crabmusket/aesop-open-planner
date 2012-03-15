/// @file AesopAction.cpp
/// Implementation of Action class as defined in AesopAction.h

#include "AesopAction.h"

namespace Aesop {
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

   void Action::condition(const Fact &fact, ConditionType type, PVal val)
   {
      Operation &op = mOperations[fact];
      op.ctype = type;
      op.cvalue = val;
   }

   void Action::effect(const Fact &fact, EffectType type, PVal val)
   {
      Operation &op = mOperations[fact];
      op.etype = type;
      op.evalue = val;
   }

   void Action::parameters(unsigned int num)
   {
      mNumParams = num;
   }
};
