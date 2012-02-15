/// @file AesopPlan.h
/// @brief Definition of Plan class.

#ifndef _AE_PLAN_H_
#define _AE_PLAN_H_

#include <vector>
#include "AesopWorldState.h"
#include "AesopActionSet.h"

namespace Aesop {
   class Plan {
   public:
      /// @brief Represents an instance of an action, the building block of a
      ///        plan.
      struct actionentry {
         /// @brief Store the action used at this step of the plan.
         ActionSet::actionID action;
         /// @brief Store the parameters associated with the action.
         WorldState::paramlist parameters;

         /// @brief Default constructor.
         actionentry() : action(), parameters() {}
         /// @brief Convenience constructor.
         /// @param[in] a Action for this entry.
         /// @param[in] p Parameters for this entry.
         actionentry(ActionSet::actionID a, WorldState::paramlist p)
            : action(a), parameters(p) {}
      };

      /// @brief Store action entries in a vector.
      typedef std::vector<actionentry> actionentries;

      /// @brief Iterate over entries.
      typedef actionentries::const_iterator const_iterator;

      /// @brief Iterator to first item in plan.
      const_iterator begin() const { return mPlan.begin(); }
      /// @brief Iterator to one-after-last item in plan.
      const_iterator end() const { return mPlan.end(); }

      /// @brief Push an action with parameters onto the end of the Plan.
      /// @param[in] action Action for this step.
      /// @param[in] params Parameters for the action.
      void push(ActionSet::actionID action, WorldState::paramlist params);

   protected:
   private:
      /// @brief Plan is a list of action entries.
      actionentries mPlan;
   };
};

#endif
