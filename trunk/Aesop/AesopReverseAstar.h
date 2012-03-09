/// @file AesopReverseAstar.h
/// Implementation of regressive A* search algorithm.

#ifndef _AE_REVERSE_ASTAR_H_
#define _AE_REVERSE_ASTAR_H_

#include <algorithm>
#include <functional>
#include "abstract/AesopWorldState.h"
#include "abstract/AesopActionSet.h"
#include "abstract/AesopObjects.h"
#include "AesopProblem.h"
#include "AesopPlan.h"
#include "abstract/AesopContext.h"

namespace Aesop {
   /// Initialise a regressive A* solution.
   /// @param[in]  init Initial world state for this problem.
   /// @param[in]  goal Desired world state for this problem.
   /// @param[out] prob Problem object to initialise.
   /// @param[out] ctx  Context for logging and profiling.
   /// @return True if initialisation was successful, false if not.
   /// @ingroup Aesop
   bool ReverseAstarInit(const WorldState &init, const WorldState &goal, Problem &prob, Context &ctx)
   {
      // Check that the predicates used by each state match.
      if(init.getPredicates() != goal.getPredicates())
      {
         //ctx.
         return false;
      }
      ctx.beginPlanning();
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

   /// Perform a single iteration in a regressive A* search.
   /// @param     prob    Problem to operate on.
   /// @param[in] actions Set of actions to operate with.
   /// @param[un] objects Set of objects that exist in the problem.
   /// @param[out] ctx    Context for logging and profiling.
   /// @return True if the algorithm should continue, false if not.
   /// @ingroup Aesop
   bool ReverseAstarIteration(Problem &prob, const ActionSet &actions, const Objects &objects, Context &ctx)
   {
      ctx.beginIteration();

      if(prob.open.empty())
      {
         ctx.failure();
         ctx.endIteration();
         return false;
      }

      pop_heap(prob.open.begin(), prob.open.end(), std::greater<Problem::openstate>());
      Problem::openstate s = prob.open.back();
      prob.open.pop_back();

      ctx.toClosed(s.ID);
      prob.closed.push_back(s);

      if(*s.state == *prob.goal)
      {
         ctx.success();
         ctx.endIteration();
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
            n.ID = prob.lastID++;
            n.state = s.state->clone();
            actions.applyReverse(it, *p, *n.state);
            n.action = it;
            n.params = *p;
            ctx.newState(n);
            // If the new state is already in the closed list, continue.
            Problem::list::const_iterator cli;
            for(cli = prob.closed.begin(); cli != prob.closed.end(); cli++)
            {
               if(*n.state == *cli->state)
               {
                  //ctx.
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
                  //ctx.
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
               //ctx.
               prob.open.push_back(n);
               push_heap(prob.open.begin(), prob.open.end(), std::greater<Problem::openstate>());
            }
         }
      }

      ctx.endIteration();
      return true;
   }

   /// Finalise a completed Problem into a Plan.
   /// @param[in]  prob Problem to operate on.
   /// @param[out] plan Plan to operate on.
   /// @param[out] ctx  Context for logging and profiling.
   /// @ingroup Aesop
   void ReverseAstarFinalise(const Problem &prob, Plan &plan, Context &ctx)
   {
      if(prob.success)
      {
         unsigned int i = prob.closed.size() - 1;
         while(i)
         {
            // Extract the action performed at this step and its parameters.
            plan.push(prob.closed[i].action, prob.closed[i].params);
            // Iterate.
            i = prob.closed[i].parent;
         }
      }
      ctx.endPlanning();
   }

   /// Perform a complete regressive A* search.
   /// @param[in]  init    Initial world state.
   /// @param[in]  goal    Desired world state.
   /// @param[in]  actions Set of actions to operate with.
   /// @param[in]  objects Set of objects that exist in the problem.
   /// @param[out] plan    Plan output.
   /// @param[out] ctx     Context for logging and profiling.
   /// @return True if a valid plan was found, false if not.
   /// @ingroup Aesop
   bool ReverseAstarSolve(const WorldState &init, const WorldState &goal,
                          const ActionSet &actions,
                          const Objects &objects,
                          Plan &plan,
                          Context &ctx)
   {
      // Initialise problem with initial and goal states.
      Problem prob;
      if(!ReverseAstarInit(init, goal, prob, ctx))
         return false;

      // Iterate.
      while(ReverseAstarIteration(prob, actions, objects, ctx)) {}

      // Finalise and return success.
      ReverseAstarFinalise(prob, plan, ctx);
      return prob.success;
   }
};

#endif
