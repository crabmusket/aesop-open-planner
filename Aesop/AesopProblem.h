/// @file AesopProblem.h
/// @brief Declaration of Problem class and functions.

#ifndef _AE_PROBLEM_H_
#define _AE_PROBLEM_H_

#include <vector>
#include "AesopWorldState.h"
#include "AesopActionSet.h"

namespace Aesop {
   /// @brief Stores planner instance data used by the planning algorithms.
   /// @ingroup Aesop
   class Problem {
   public:
      /// @brief Was a plan successfully created?
      bool success;

      /// @brief State this problem is trying to reach.
      const WorldState *goal;

      /// @brief Default constructor.
      Problem();

      /// @brief Default destructor.
      ~Problem();

      /// @brief Store world states in the open list.
      struct openstate {
         /// @brief Intermediate WorldState.
         WorldState *state;

         /// @brief Total cost of this intermediate state.
         float cost,
         /// @brief Cost accrued to get to this state.
            G,
         /// @brief Heuristic cost to get to goal state.
            H;

         /// @brief State in the closed list that this state is reached from.
         unsigned int parent;

         /// @brief The action used to get here from the previous state.
         ActionSet::const_iterator action;

         /// @brief Parameters to our action.
         WorldState::paramlist params;

         /// @brief Default constructor.
         openstate()
         {
            state = NULL;
            cost = G = H = 0.0f;
            parent = 0;
            action = ActionSet::actionID();
            params = WorldState::paramlist();
         }

         /// @brief Compare based on cost.
         bool operator>(const openstate &s) const
         { return cost > s.cost; }

         /// @brief Compare based on cost.
         bool operator<(const openstate &s) const
         { return cost < s.cost; }

         /// @brief Equality is based on the state represented, not auxiliary
         ///        data.
         bool operator==(const openstate &s) const
         { return state == s.state; }
         bool operator!=(const openstate &s) const
         { return !operator==(s); }
      };

      /// @brief Open and closed lists use the same data type.
      typedef std::vector<openstate> list;

      /// @brief Open list.
      list open;

      /// @brief Closed list.
      list closed;
   protected:
   private:
   };
};

#endif
