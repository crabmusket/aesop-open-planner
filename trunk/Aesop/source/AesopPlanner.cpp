/// @file AesopPlanner.cpp
/// @brief Implementation of Planner class as defined in Aesop.h

#include "Aesop.h"

#include <functional>
#include <algorithm>
#include <vector>

namespace ae {
   /// @brief A WorldState instance used during planning.
   /// @see Planner
   struct IntermediateState {
      /// @brief ID number of this IntermediateState within the current plan.
      unsigned int ID;
      /// @brief State of the world at this step.
      WorldState state;
      /// @brief Current cost to get to this state from starting state.
      float G;
      /// @brief Guess at cost to get from this state to goal.
      float H;
      /// @brief The sum of G and H.
      float F;
      /// @brief IntermediateState leading to this one.
      unsigned int prev;
      /// @brief Action leading to this one.
      const Action *ac;

      /// @brief Default constructor.
      IntermediateState(unsigned int id)
      {
         G = 0;
         H = 0;
         F = 0;
         prev = 0;
         ac = NULL;
         ID = id;
      }

      /// @brief Compare based on F score.
      bool operator>(const IntermediateState s) const
      { return F > s.F; }

      /// @brief Compare based on F score.
      bool operator<(const IntermediateState s) const
      { return F < s.F; }

      /// @brief Equality is based on the state represented, not auxiliary
      ///        data.
      bool operator==(const IntermediateState &s) const
      { return state == s.state; }
   };

   /// @class Planner
   ///
   /// A Planner object actually performs plan queries on the world state.
   /// It represents an entire planning state, with its own start and end
   /// states and plan-specific data.
   /// This will include, among other things, a set of vetoed Actions (for
   /// example, Actions that we tried but failed in practis, and we now
   /// want to exclude from our planning process temporarily).

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
      std::vector<IntermediateState>::iterator oli;
      // Closed list.
      std::vector<IntermediateState> cl;
      std::vector<IntermediateState>::const_iterator cli;

      // Current IntermediateState ID number.
      unsigned int id = 0;

      // Push goal onto the open list.
      ol.push_back(IntermediateState(id)); id++;
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

         if(log) log->logEvent("Moving state %d from open to closed.", s.ID);

         // Add to closed list.
         cl.push_back(s);

         // Check for completeness.
         if(s.state == *mStart)
         {
            success = true;
            break;
         }

         // Find all actions we can use that may result in the current state.
         ActionSet::const_iterator it;
         for(it = mActions->begin(); it != mActions->end(); it++)
         {
            if(s.state.actionPostMatch(&*it))
            {
               IntermediateState n(id); id++;
               // Copy the current state, then apply the Action to it in
               // reverse to get the previous state.
               n.state = s.state;
               n.state.applyActionReverse(&*it);

               // Check to see if the world state is in the closed list.
               bool found = false;
               for(cli = cl.begin(); cli != cl.end(); cli++)
               {
                  if(n.state == cli->state)
                  {
                     found = true;
                     break;
                  }
               }
               if(found)
                  continue;

               // H (heuristic) cost is the estimated number of Actions to get
               // from new state to start.
               n.H = (float)WorldState::comp(n.state, *mStart);
               // G cost is the total weight of all Actions we've taken to get
               // to this state. By default, the cost of an Action is 1.
               n.G = s.G + it->getCost();
               // Save this to avoid recalculating every time.
               n.F = n.G + n.H;
               // Remember Action we used to to this state.
               n.ac = &*it;
               // Predecessor is the last state to be added to the closed list.
               n.prev = cl.size() - 1;

               // Check to see if the world state is already in the open list.
               for(oli = ol.begin(); oli != ol.end(); oli++)
               {
                  if(n.state == oli->state && n < *oli)
                  {
                     // We've found a more efficient way of getting here.
                     *oli = n;
                     // Reorder the heap.
                     make_heap(ol.begin(), ol.end(),
                        std::greater<IntermediateState>());

                     if(log) log->logEvent("Updating state %d to F=%f",
                        oli->ID, oli->G + oli->H);
                     break;
                  }
               }
               // No match found in open list.
               if(oli == ol.end())
               {
                  // Add the new intermediate state to the open list.
                  ol.push_back(n);
                  // Heapify open list.
                  push_heap(ol.begin(), ol.end(), std::greater<IntermediateState>());

                  if(log) log->logEvent("Pushing state %d via action \"%s\" onto open list with score F=%f.",
                     n.ID, it->getName().c_str(), n.G + n.H);
               }
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
