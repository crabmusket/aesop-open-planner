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

   Action::Action()
   {
   }

   Action::~Action()
   {
   }

   void Action::addRequired(const Statement st)
   {
      mRequired.push_back(st);
   }

   void Action::addRequired(const Statement sts[], unsigned int size)
   {
      while(size)
         addRequired(sts[--size]);
   }

   void Action::addSet(const Statement st)
   {
      mPostSet.push_back(st);
   }

   void Action::addSet(const Statement sts[], unsigned int size)
   {
      while(size)
         addSet(sts[--size]);
   }
 
   void Action::addClear(const PName pred)
   {
      mPostClear.push_back(pred);
   }

   void Action::addClear(const PName preds[], unsigned int size)
   {
      while(size)
         addClear(preds[--size]);
   }

};