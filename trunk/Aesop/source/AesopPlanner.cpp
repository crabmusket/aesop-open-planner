/// @file AesopPlanner.cpp
/// @brief Implementation of Planner class as defined in Aesop.h

#include "Aesop.h"

#include <functional>
#include <algorithm>
#include <vector>

namespace ae {
   /// @struct IntermediateState
   /// @brief A WorldState instance used during planning.
   /// @see Planner
   struct IntermediateState {
      /// @brief State of the world at this step.
      WorldState state;
      /// @brief Current cost to get to this state from starting state.
      unsigned int G;
      /// @brief Guess at cost to get from this state to goal.
      unsigned int H;
      /// @brief IntermediateState leading to this one.
      unsigned int prev;
      /// @brief Action leading to this one.
      const Action *ac;

      /// @brief Default constructor.
      IntermediateState()
      {
         G = 0;
         H = 0;
         prev = 0;
         ac = NULL;
      }

      /// @brief What makes one IntermediateState greater than another?
      /// The answer is the sum of F and G.
      bool operator>(const IntermediateState s) const
      { return (G + H) > (s.G + s.H); }

      bool operator==(const IntermediateState &s) const
      { return state == s.state; }
   };

   /// @class Planner
   ///
   /// 

   Planner::Planner(const WorldState *start, const WorldState *goal, const ActionSet *set)
   {
      setStart(start);
      setGoal(goal);
      setActions(set);
   }

   Planner::Planner()
   {
      setStart(NULL);
      setGoal(NULL);
      setActions(NULL);
   }

   Planner::~Planner()
   {
   }

   void Planner::setStart(const WorldState *start)
   {
      mStart = start;
   }

   void Planner::setGoal(const WorldState *goal)
   {
      mGoal = goal;
   }

   void Planner::setActions(const ActionSet *set)
   {
      mActions = set;
   }

   const Plan& Planner::getPlan() const
   {
      return mPlan;
   }

   bool Planner::plan(AesopLogger *log)
   {
      // Open list.
      std::vector<IntermediateState> ol;
      // Closed list.
      std::vector<IntermediateState> cl;

      // Push start onto the open list.
      ol.push_back(IntermediateState());
      ol.back().state = *mGoal;

      // Did we find a plan?
      bool success = false;

      // Main loop of A* search.
      while(!ol.empty())
      {
         // Remove best IntermediateState from open list.
         pop_heap(ol.begin(), ol.end(), std::greater<IntermediateState>());
         IntermediateState s = ol.back();
         ol.pop_back();

         // Add to closed list.
         cl.push_back(s);

         // Check for completeness.
         if(s.state == *mStart)
         {
            success = true;
            break;
         }

         // For each action we could perform to get to this state:
         //    Compute the state that would come before this action temporally.
         //    If it's in the closed list, ignore it.
         //    If it's already in the ol, update G and H costs as necessary.
         //    Otherwise, add it.

         // Find all actions we can use that may result in the current state.
         ActionSet::const_iterator it;
         for(it = mActions->begin(); it != mActions->end(); it++)
         {
            if(s.state.actionPostMatch(&*it))
            {
               // Add a new intermediate state to the open list.
               ol.push_back(IntermediateState());
               // Copy the current state, then apply the Action to it in
               // reverse to get the previous state.
               ol.back().state = s.state;
               ol.back().state.applyActionReverse(&*it);
               ol.back().H = WorldState::comp(ol.back().state, *mStart);
               // At the moment, each action costs 1.
               ol.back().G = s.G + 1;
               ol.back().ac = &*it;
               // Remember position in closed list of our predecessor.
               ol.back().prev = cl.size() - 1;
               // Heapify open list.
               push_heap(ol.begin(), ol.end(), std::greater<IntermediateState>());
            }
         }
      }

      // Work backwards up the closed list to get out plan.
      mPlan.clear();
      if(success)
      {
         unsigned int i = cl.size() - 1;
         while(i)
         {
            // Extract the Action performed at this step.
            mPlan.push_back(*cl[i].ac);
            // Iterate.
            i = cl[i].prev;
         }
      }

      return success;
   }
};
