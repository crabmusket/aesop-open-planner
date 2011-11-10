/// @file AesopAction.cpp
/// @brief Implementation of Action class as defined in Aesop.h

#include "Aesop.h"

namespace ae {
   /// @class Action
   ///
   /// Based on the STRIPS concept of an action, an Action represents an atomic
   /// change we can make to the world, and is the building block of all plans
   /// made with Aesop.
   ///
   /// An Action is essentially a change to the world state. To perform an
   /// Action, the world must be in a certain state. After the Action is
   /// performed, certain changes will be made to that world state.

   Action::Action()
   {
   }

   Action::~Action()
   {
   }

   const Action::storage& Action::getRequired() const { return mRequired; }
   const Action::storage& Action::getVetoed()   const { return mRequiredNot; }
   const Action::storage& Action::getSet()      const { return mPostSetTrue; }
   const Action::storage& Action::getReset()    const { return mPostSetFalse; }
   const Action::storage& Action::getCleared()  const { return mPostClear; }
};