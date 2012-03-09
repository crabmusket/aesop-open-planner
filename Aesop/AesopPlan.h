/// @file AesopPlan.h
/// Definition of Plan class.

#ifndef _AE_PLAN_H_
#define _AE_PLAN_H_

#include <vector>
#include "abstract/AesopWorldState.h"
#include "abstract/AesopActionSet.h"

namespace Aesop {
   class Plan {
   public:
      /// Represents an instance of an action, the building block of a plan.
      /// @ingroup Aesop
      struct actionentry {
         /// Store the action used at this step of the plan.
         ActionSet::actionID action;
         /// Store the parameters associated with the action.
         WorldState::paramlist parameters;

         /// Default constructor.
         actionentry() : action(), parameters() {}
         /// Convenience constructor.
         /// @param[in] a Action for this entry.
         /// @param[in] p Parameters for this entry.
         actionentry(ActionSet::actionID a, WorldState::paramlist p)
            : action(a), parameters(p) {}
      };

      /// Store action entries in a vector.
      typedef std::vector<actionentry> actionentries;

      /// Iterate over entries.
      typedef actionentries::const_iterator const_iterator;

      /// Iterator to first item in plan.
      const_iterator begin() const { return mPlan.begin(); }
      /// Iterator to one-after-last item in plan.
      const_iterator end() const { return mPlan.end(); }

      /// Push an action with parameters onto the end of the Plan.
      /// @param[in] action Action for this step.
      /// @param[in] params Parameters for the action.
      void push(ActionSet::actionID action, WorldState::paramlist params);

   protected:
   private:
      /// Plan is a list of action entries.
      actionentries mPlan;
   };
};

#endif
