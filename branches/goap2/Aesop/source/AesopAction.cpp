/// @file AesopAction.cpp
/// @brief Implementation of Action class as defined in AesopAction.h

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

   void Action::addRequired(PName name, PVal val)
   {
      mRequired[name] = val;
   }

   void Action::addSet(PName name, PVal val)
   {
      mPostSet[name] = val;
   }
 
   void Action::addClear(PName pred)
   {
      // Check if predicate name already exists in list.
      pnamelist::const_iterator it;
      for(it = mPostClear.begin(); it != mPostClear.end(); it++)
         if(*it == pred)
            break;
      // Not found; add.
      if(it == mPostClear.end())
         mPostClear.push_back(pred);
   }

   void Action::addRequiredParam(PName name, unsigned int param)
   {
      if(param < mNumParams)
         mRequiredParam[name] = param;
   }

   void Action::addSetParam(PName name, unsigned int param)
   {
      if(param < mNumParams)
         mPostSetParam[name] = param;
   }
};
