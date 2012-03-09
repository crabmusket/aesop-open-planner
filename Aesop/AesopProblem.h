/// @file AesopProblem.h
/// Declaration of Problem class and functions.

#ifndef _AE_PROBLEM_H_
#define _AE_PROBLEM_H_

#include <vector>
#include "abstract/AesopWorldState.h"
#include "abstract/AesopActionSet.h"

namespace Aesop {
   /// Stores planner instance data used by the planning algorithms.
   /// @ingroup Aesop
   class Problem {
   public:
      /// Was a plan successfully created?
      bool success;

      /// State this problem is trying to reach.
      const WorldState *goal;

      /// Default constructor.
      Problem();

      /// Default destructor.
      ~Problem();

      /// Store world states in the open list.
      struct openstate {
         /// Intermediate WorldState.
         WorldState *state;

         /// Identifier of this state.
         unsigned int ID;

         /// Total cost of this intermediate state.
         float cost,
         /// Cost accrued to get to this state.
            G,
         /// Heuristic cost to get to goal state.
            H;

         /// State in the closed list that this state is reached from.
         unsigned int parent;

         /// The action used to get here from the previous state.
         ActionSet::const_iterator action;

         /// Parameters to our action.
         WorldState::paramlist params;

         /// Default constructor.
         openstate()
         {
            ID = 0;
            state = NULL;
            cost = G = H = 0.0f;
            parent = 0;
            action = ActionSet::actionID();
            params = WorldState::paramlist();
         }

         /// Compare based on cost.
         bool operator>(const openstate &s) const
         { return cost > s.cost; }

         /// Compare based on cost.
         bool operator<(const openstate &s) const
         { return cost < s.cost; }

         /// Equality is based on the state represented, not auxiliary
         ///        data.
         bool operator==(const openstate &s) const
         { return state == s.state; }
         bool operator!=(const openstate &s) const
         { return !operator==(s); }
      };

      /// Open and closed lists use the same data type.
      typedef std::vector<openstate> list;

      /// Open list.
      list open;

      /// Closed list.
      list closed;

      /// ID counter for states.
      unsigned int lastID;
   protected:
   private:
   };
};

#endif
