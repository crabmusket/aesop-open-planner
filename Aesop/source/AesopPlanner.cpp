/// @file AesopPlanner.cpp
/// @brief Implementation of Planner class as defined in Aesop.h

#include "Aesop.h"

#include <functional>
#include <algorithm>
#include <vector>

namespace ae {
   /// @class Planner
   ///
   /// A Planner object actually performs plan queries on the world state.
   /// It represents an entire planning state, with its own start and end
   /// states and plan-specific data.
   /// This will include, among other things, a set of vetoed Actions (for
   /// example, Actions that we tried but failed in practise, and we now
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

   /// This method back-tracks through the planning space and extracts a plan
   /// from the intermediate states that exist in the closed list. After that,
   /// the open and closed lists are cleared.
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
         mPlan.back().params = mClosedList[i].params;
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
            paramset pset;
            // Get number of params and create a set of paramlists.
            unsigned int nparams = ac->getNumParams();
            if(nparams)
            {
               // Get the param values that the world state requires.
               paramlist p;
               s.state.actionGetParams(ac, p);
               // Allow the Action to fill in the parameters after some have
               // been specified.
               ac->getParams(ctx, p, pset);
               // Loop on the parameter set.
               paramset::iterator pit;
               for(pit = pset.begin(); pit != pset.end(); pit++)
                  attemptIntermediate(ctx, s, ac, it->second, &*pit);
            }
            else
               attemptIntermediate(ctx, s, ac, it->second, NULL);
         }
      }
      else
         return false;

      return true;
   }

   void Planner::attemptIntermediate(Context *ctx, IntermediateState &s, const Action* ac, float pref, paramlist *plist)
   {
      if(!s.state.actionPostMatch(ac, plist))
         return;

      IntermediateState n(mId); mId++;
      // Copy the current state, then apply the Action to it in reverse to get
      // the previous state.
      n.state = s.state;
      n.state.applyActionReverse(ac, plist);

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
      n.G = s.G + ac->getCost() * pref;
      // Save this to avoid recalculating every time.
      n.F = n.G + n.H;
      // Remember Action we used to to this state.
      n.ac = ac;
      if(plist)
         n.params = *plist;
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
            n.ID, ac->getName().c_str(), n.G + n.H);
      }
   }
};

///
/// @class Planner
/// Note that careful use of the finaliseSlicedPlan() method enables a plan to
/// be 'queued' while another plan is being stored.
/// @code
///    // Create some plan.
///    planner.setStart(&start);
///    planner.setGoal(&goal);
///    planner.plan(&context);
///    // Setup a new planning space.
///    planner.setStart(&newStart);
///    planner.setGoal(&newGoal);
///    // Calculate the plan, but do not finalise it.
///    planner.initSlicedPlan(&context);
///    while(planner.isPlanning())
///       updateSlicedPlan(context);
/// @endcode
/// Now, upon the next call to finaliseSlicedPlan(), the current plan will
/// be replaced by the already-completed new one. The planning loop could be
/// spread out over multiple loops of an application, while an agent enacts
/// the first plan, for example.
///