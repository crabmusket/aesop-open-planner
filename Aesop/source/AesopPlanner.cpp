/// @file AesopPlanner.cpp
/// Implementation of Planner class as defined in AesopPlanner.h

#include "AesopPlanner.h"

#include <functional>
#include <algorithm>
#include <vector>
#include <cmath>

namespace Aesop {
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
      mPlanning = false;
      mId = 0;
   }

   Planner::Planner()
   {
      Planner(NULL, NULL, NULL);
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

   bool Planner::isPlanning() const
   {
      return mPlanning;
   }

   const Plan& Planner::getPlan() const
   {
      return mPlan;
   }

   /// This method is actually just a wrapper for a series of calls to the
   /// sliced planning methods.
   bool Planner::plan(Context *ctx)
   {
      // Try to start planning.
      if(!initSlicedPlan(ctx))
         return false;

      while(isPlanning())
      {
         // Increment plan and capture failure.
         if(!updateSlicedPlan(ctx))
            return false;
         // If planning has halted, we must have been successful.
         if(!isPlanning())
         {
            finaliseSlicedPlan(ctx);
            return true;
         }
      }

      // No plan found.
      return false;
   }

   bool Planner::initSlicedPlan(Context *ctx)
   {
      // Validate pointers.
      if(!mStart || !mGoal || !mActions)
      {
         if(ctx) ctx->logEvent("Planning failed due to unset start, goal or action set!");
         return false;
      }

      if(ctx) ctx->logEvent("Starting new plan.");

      // Reset intermediate data.
      mPlanning = true;
      mOpenList.clear();
      mClosedList.clear();
      mId = 0;

      if(ctx) ctx->logEvent("Pushing starting state onto open list.");

      // Push initial state onto the open list.
      mOpenList.push_back(IntermediateState(mId)); mId++;
      mOpenList.back().state = *mGoal;

      return true;
   }

   void Planner::finaliseSlicedPlan(Context *ctx)
   {
      if(ctx) ctx->logEvent("Finalising plan!");
      // Work backwards up the closed list to get the final plan.
      mPlan.clear();
      unsigned int i = mClosedList.size() - 1;
      while(i)
      {
         // Extract the Action performed at this step.
         mPlan.push_back(ActionEntry());
         mPlan.back().ac = mClosedList[i].ac;
         memcpy(&mPlan.back().params[0], &mClosedList[i].params[0], sizeof(PParam) * PARAMS);
         // Iterate.
         i = mClosedList[i].prev;
      }
      // Purge intermediate results.
      mOpenList.clear();
      mClosedList.clear();
      mPlanning = false;
   }

   bool Planner::updateSlicedPlan(Context *ctx)
   {
      // Main loop of A* search.
      if(!mOpenList.empty())
      {
         // Remove best IntermediateState from open list.
         pop_heap(mOpenList.begin(), mOpenList.end(), std::greater<IntermediateState>());
         IntermediateState s = mOpenList.back();
         mOpenList.pop_back();

         if(ctx) ctx->logEvent("Moving state %d from open to closed.", s.ID);

         // Add to closed list.
         mClosedList.push_back(s);

         // Check for completeness.
         if(s.state == *mStart)
         {
            mPlanning = false;
            return true;
         }

         // Find all actions we can use that may result in the current state.
         ActionSet::const_iterator it;
         for(it = mActions->begin(); it != mActions->end(); it++)
         {
            const Action *ac = it->first;
            if(!ac)
               continue;
            paramset params;
            // Get number of params and create a set of paramlists.
            unsigned int nparams = ac->getNumParams();
            if(nparams && mObjects.size())
            {
               // Permute defined objects to feed as parameters.
               unsigned int permutations = (unsigned int)pow((float)mObjects.size(), (float)nparams);
               params.resize(permutations);
               std::vector<unsigned int> objs(nparams, 0);
               for(unsigned int i = 0; i < permutations; i++)
               {
                  unsigned int j;
                  for(j = 0; j < nparams; j++)
                     params[i][j] = objs[j];
                  unsigned int obj = ++objs[--j];
                  while(obj == mObjects.size() && j > 0)
                  {
                     objs[j] = 0;
                     j--;
                     objs[j]++;
                  }
               }
               // Loop on the parameter set.
               paramset::iterator pit;
               for(pit = params.begin(); pit != params.end(); pit++)
                  attemptIntermediate(ctx, s, *ac, it->second, &*pit);
            }
            else
               attemptIntermediate(ctx, s, *ac, it->second, NULL);
         }
      }
      else
         return false;

      return false;
   }

   void Planner::attemptIntermediate(Context *ctx, IntermediateState &s, const Action &ac, float pref, paramlist *plist)
   {
      if(!s.state.postMatch(ac, plist))
         return;

      IntermediateState n(mId); mId++;
      // Copy the current state, then apply the Action to it in reverse to get
      // the previous state.
      n.state = s.state;
      n.state.applyReverse(ac, plist);

      closedlist::const_iterator cli;
      // Check to see if the world state is in the closed list.
      bool found = false;
      for(cli = mClosedList.begin(); cli != mClosedList.end(); cli++)
      {
         if(n.state == cli->state)
         {
            found = true;
            break;
         }
      }
      if(found)
         return;

      // H (heuristic) cost is the estimated number of Actions to get from new
      // state to start.
      n.H = (float)WorldState::comp(n.state, *mStart);
      // G cost is the total weight of all Actions we've taken to get to this
      // state. By default, the cost of an Action is 1.
      n.G = s.G + ac.getCost() * pref;
      // Save this to avoid recalculating every time.
      n.F = n.G + n.H;
      // Remember Action we used to to this state.
      n.ac = &ac;
      if(plist)
         memcpy(&n.params[0], &plist[0], sizeof(PParam) * PARAMS);
      // Predecessor is the last state to be added to the closed list.
      n.prev = mClosedList.size() - 1;

      openlist::iterator oli;
      // Check to see if the world state is already in the open list.
      for(oli = mOpenList.begin(); oli != mOpenList.end(); oli++)
      {
         if(n.state == oli->state && n < *oli)
         {
            // We've found a more efficient way of getting here.
            *oli = n;
            // Reorder the heap.
            make_heap(mOpenList.begin(), mOpenList.end(),
               std::greater<IntermediateState>());

            if(ctx) ctx->logEvent("Updating state %d to F=%f",
               oli->ID, oli->G + oli->H);
            break;
         }
      }
      // No match found in open list.
      if(oli == mOpenList.end())
      {
         // Add the new intermediate state to the open list.
         mOpenList.push_back(n);
         // Heapify open list.
         push_heap(mOpenList.begin(), mOpenList.end(), std::greater<IntermediateState>());

         if(ctx) ctx->logEvent("Pushing state %d via action \"%s\" onto open list with score F=%f.",
            n.ID, ac.getName().c_str(), n.G + n.H);
      }
   }
};
