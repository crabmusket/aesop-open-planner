/// @file AesopPlanner.h
/// @brief Defines Planner class.

#ifndef _AE_PLANNER_H_
#define _AE_PLANNER_H_

#include "AesopTypes.h"
#include "AesopWorldState.h"
#include "AesopContext.h"

namespace Aesop {
   /// @brief A context in which we can make plans.
   class Planner {
   public:
      /// @brief Set our starting WorldState.
      /// @param[in] start Pointer to a WorldState.
      void setStart(const WorldState *start);

      /// @brief Set our goal state.
      /// @param[in] goal Pointer to a WorldState.
      void setGoal(const WorldState *goal);

      /// @brief Create a plan.
      /// @param[in] ctx Context object to record the Planner's activity.
      /// @return True if the plan was successfully calculated, false if no
      ///         plan exists or something went wrong in the planning process.
      bool plan(Context *ctx = NULL);

      /// @brief Start a sliced plan.
      /// @param[in] ctx Context object to record the Planner's activity.
      /// @return True if the plan was successfully initialised, false if
      ///         something went wrong in initialisation.
      bool initSlicedPlan(Context *ctx = NULL);

      /// @brief Update a sliced plan.
      /// @param[in] ctx Context object to record the Planner's activity.
      /// @return False if a valid plan was not found; true otherwise.
      bool updateSlicedPlan(Context *ctx = NULL);

      /// @brief Output the result of a computed plan to 
      /// @param[in] ctx Context object to record the Planner's activity.
      void finaliseSlicedPlan(Context *ctx = NULL);

      /// @brief US English spelling of finaliseSlicedPlan. 'Cause I'm a nice guy.
      /// @see Planner::finaliseSlicedPlan
      inline void finalizeSlicedPlan(Context *ctx = NULL)
      { finaliseSlicedPlan(ctx); }

      /// @brief Is this Planner in the middle of processing a sliced plan?
      /// @return 
      bool isPlanning() const;

      /// @brief Get the currently constructed plan.
      /// @return A Plan.
      const Plan& getPlan() const;

      /// @brief Set the ActionSet we can use.
      /// @param[in] set The ActionSet to pull from.
      void setActions(const ActionSet *set);

      /// @brief Value constructor.
      /// @param[in] start Starting world state.
      /// @param[in] goal  Target world state.
      /// @param[in] set   ActionSet that defines the Actions we may perform.
      Planner(const WorldState *start, const WorldState *goal, const ActionSet *set);

      /// @brief Default constructor.
      Planner();
      /// @brief Default destructor.
      ~Planner();

   protected:

   private:
      /// @brief A WorldState instance used during planning.
      struct IntermediateState {
         /// @brief ID number of this IntermediateState within the current plan.
         /// Not really used, except to identify states for debugging purposes.
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
         /// @brief Parameters to pass to our Action.
         paramlist params;

         /// @brief Default constructor.
         IntermediateState(unsigned int id)
         {
            G = H = F = 0.0f;
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
      typedef std::vector<IntermediateState> openlist;
      typedef std::vector<IntermediateState> closedlist;

      /// @brief Starting state.
      /// Not allowed to modify this.
      const WorldState *mStart;
      /// @brief Goal state.
      /// Not allowed to modify this.
      const WorldState *mGoal;
      /// @brief A* algorithm open list.
      openlist mOpenList;
      /// @brief A* algorithm closed list.
      closedlist mClosedList;
      /// @brief Are we still working on a sliced plan?
      bool mPlanning;
      /// @brief IntermediateState ID number for debug purposes.
      /// @todo Find a better way to identify states!
      unsigned int mId;
      /// @brief Current plan to get from mStart to mGoal.
      Plan mPlan;
      /// @brief Set of Actions we are allowed to perform.
      const ActionSet *mActions;

      /// @brief Internal function used by pathfinding.
      void attemptIntermediate(Context *ctx, IntermediateState &s, const Action* ac, float pref, paramlist *plist);
   };
};

#endif
