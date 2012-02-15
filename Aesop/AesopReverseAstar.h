/// @file AesopReverseAstar.h
/// @brief Implementation of regressive A* search algorithm.

#ifndef _AE_REVERSE_ASTAR_H_
#define _AE_REVERSE_ASTAR_H_

#include <algorithm>
#include <functional>
#include "AesopWorldState.h"
#include "AesopActionSet.h"
#include "AesopObjects.h"
#include "AesopProblem.h"
#include "AesopPlan.h"

namespace Aesop {
   /// @brief Initialise a regressive A* solution.
   /// @param[in]  init Initial world state for this problem.
   /// @param[in]  goal Desired world state for this problem.
   /// @param[out] prob Problem object to initialise.
   /// @return True if initialisation was successful, false if not.
   bool ReverseAstarInit(const WorldState &init, const WorldState &goal, Problem &prob)
   {
      // Check that the predicates used by each state match.
      if(init.getPredicates() != goal.getPredicates())
         return false;
      // Goal is actually initial state since we're doing a regressive search.
      prob.goal = &init;
      // Clear problem data.
      prob.open.clear();
      prob.closed.clear();
      prob.success = false;
      // Push the first state onto the open list.
      prob.open.push_back(Problem::openstate());
      prob.open.back().state = goal.clone();
      return true;
   }

   /// @brief Perform a single iteration in a regressive A* search.
   /// @param     prob    Problem to operate on.
   /// @param[in] actions Set of actions to operate with.
   /// @param[un] objects Set of objects that exist in the problem.
   /// @return True if the algorithm should continue, false if not.
   bool ReverseAstarIteration(Problem &prob, const ActionSet &actions, const Objects &objects)
   {
      if(prob.open.empty())
      {
         printf("Open list is empty. Finishing.\n");
         return false;
      }

      pop_heap(prob.open.begin(), prob.open.end(), std::greater<Problem::openstate>());
      Problem::openstate s = prob.open.back();
      prob.open.pop_back();

      printf("Transferring state %s to closed list.\n", s.state->repr().c_str());
      prob.closed.push_back(s);

      if(*s.state == *prob.goal)
      {
         printf("    State matches goal. Finishing.\n");
         prob.success = true;
         return false;
      }

      // For each action we can take
      ActionSet::const_iterator it;
      for(it = actions.begin(); it != actions.end(); it++)
      {
         // Get list of parameter combinations.
         ActionSet::paramcombos plist;
         actions.getParamList(it, plist, objects);
         ActionSet::paramcombos::const_iterator p;
         // For each valid parameter combination:
         for(p = plist.begin(); p != plist.end(); p++)
         {
            // If the action doesn't post-match this world state, continue.
            if(!actions.postMatch(it, *p, *s.state))
               continue;
            // Create a new world state by applying the action in reverse.
            Problem::openstate n;
            n.state = s.state->clone();
            actions.applyReverse(it, *p, *n.state);
            n.action = it;
            n.params = *p;
            printf("Creating new state %s via action %s.\n", n.state->repr().c_str(), actions.repr(it).c_str());
            // If the new state is already in the closed list, continue.
            Problem::list::const_iterator cli;
            for(cli = prob.closed.begin(); cli != prob.closed.end(); cli++)
            {
               if(*n.state == *cli->state)
               {
                  printf("    State already exists in closed list; aborting.\n");
                  delete n.state;
                  break;
               }
            }
            if(cli != prob.closed.end())
               continue;
            // Parent is last item in closed list.
            n.parent = prob.closed.size() - 1;
            // Calculate cost.
            n.G = s.G + 1;
            n.H = (float)s.state->compare(*prob.goal);
            n.cost = n.G + n.H;
            // Check whether state is already in the open list; if so, we may
            // update its cost.
            Problem::list::iterator oli;
            // Check to see if the world state is already in the open list.
            for(oli = prob.open.begin(); oli != prob.open.end(); oli++)
            {
               if(*n.state == *oli->state && n < *oli)
               {
                  printf("Updating state %s with action %s", n.state->repr().c_str(), actions.repr(it).c_str());
                  // We've found a more efficient way of getting here.
                  *oli = n;
                  // Reorder the heap.
                  make_heap(prob.open.begin(), prob.open.end(),
                     std::greater<Problem::openstate>());
                  break;
               }
            }
            // Push onto the open list if not already in it.
            if(oli == prob.open.end())
            {
               printf("    Pushing new state onto open list with cost %.3f\n", n.cost);
               prob.open.push_back(n);
               push_heap(prob.open.begin(), prob.open.end(), std::greater<Problem::openstate>());
            }
         }
      }

      return true;
   }

   /// @brief Finalise a completed Problem into a Plan.
   /// @param[in]  prob Problem to operate on.
   /// @param[out] plan Plan to operate on.
   void ReverseAstarFinalise(const Problem &prob, Plan &plan)
   {
      if(!prob.closed.size())
         return;
      unsigned int i = prob.closed.size() - 1;
      while(i)
      {
         // Extract the action performed at this step and its parameters.
         plan.push(prob.closed[i].action, prob.closed[i].params);
         // Iterate.
         i = prob.closed[i].parent;
      }
   }

   /// @brief Perform a complete regressive A* search.
   /// @param[in]  init    Initial world state.
   /// @param[in]  goal    Desired world state.
   /// @param[in]  actions Set of actions to operate with.
   /// @param[in]  objects Set of objects that exist in the problem.
   /// @param[out] plan    Plan output.
   /// @return True if a valid plan was found, false if not.
   bool ReverseAstarSolve(const WorldState &init, const WorldState &goal,
                          const ActionSet &actions,
                          const Objects &objects,
                          Plan &plan)
   {
      // Initialise problem with initial and goal states.
      Problem prob;
      if(!ReverseAstarInit(init, goal, prob))
         return false;

      // Iterate.
      while(ReverseAstarIteration(prob, actions, objects)) {}

      // Finalise and return success.
      if(prob.success)
         ReverseAstarFinalise(prob, plan);
      return prob.success;
   }
};

#endif

/*
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
*/