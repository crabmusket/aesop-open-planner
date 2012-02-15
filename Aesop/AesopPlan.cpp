/// @file AesopPlan.cpp
/// @brief Implementation of Plan class defined in AesopPlan.h

#include "AesopPlan.h"

namespace Aesop {
   void Plan::push(ActionSet::actionID action, WorldState::paramlist params)
   {
      mPlan.push_back(actionentry(action, params));
   }
};
