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
   }

   Action::Action()
   {
   }

   Action::~Action()
   {
   }

   void Action::addRequired(PName name, PVal val)
   {
      mRequired[name] = val;
   }

   /*void Action::addRequired(const Statement sts[], unsigned int size)
   {
      while(size)
         addRequired(sts[--size]);
   }*/

   void Action::addSet(PName name, PVal val)
   {
      mPostSet[name] = val;
   }

   /*void Action::addSet(const Statement sts[], unsigned int size)
   {
      while(size)
         addSet(sts[--size]);
   }*/
 
   void Action::addClear(PName pred)
   {
      mPostClear.push_back(pred);
   }

   /*void Action::addClear(const PName preds[], unsigned int size)
   {
      while(size)
         addClear(preds[--size]);
   }*/

};