//
// Copyright (C) 2011-2012 by Daniel Buckmaster (dan.buckmaster@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

/// @file Aesop.h
/// @brief Main file for Aesop open planning library.

/// @mainpage
/// Aesop is a library of classes and functions that implement a STRIPS-like
/// dynamic planner in C++. The goal of the planner is to take an initial world
/// state, a set of actions that operate on the world state, and put together
/// a sequence of actions such that the world is transformed into some desired
/// final state.
///
/// For more information:
/// <ul>
///   <li><a href="http://en.wikipedia.org/wiki/STRIPS">STRIPS - Wikipedia</a></li>
///   <li><a href="http://web.media.mit.edu/~jorkin/goap.html">Goal-Oriented Action Planning</a></li>
/// </ul>

#ifndef _AE_AESOP_H_
#define _AE_AESOP_H_

#include <string.h>
#include <string>
#include <map>
#include <list>
#include <vector>

#include "AesopConfig.h"

/// @namespace ae
/// @brief Includes all Aesop functions and classes.
namespace ae {
   /// @brief Represents the name of a predicate.
   typedef std::string PName;
   /// @brief Represents the value of a predicate.
   typedef unsigned char PVal;
   /// @brief Method of storing Predicates and their values.
   typedef std::map<PName, PVal> worldrep;
   /// @brief Simply stores a list of predicate names.
   typedef std::vector<PName> pnamelist;

   /// @brief An atomic change that can be made to the world state.
   class Action {
   public:
      /// @brief Get the names of the statements that must be TRUE.
      const worldrep& getRequired() const { return mRequired; }
      /// @brief Get the names of statements we set to some value.
      const worldrep& getSet()      const { return mPostSet; }
      /// @brief Get the names of statements we UNSET.
      const pnamelist& getCleared()  const { return mPostClear; }

      /// @brief Add a single statement to our list of required statements.
      /// @param[in] name Name of the predicate the statement refers to.
      /// @param[in] val  Value the predicate is required to take.
      void addRequired(PName name, PVal val);

      /// @brief Add a single statement to our list of predicates to set after
      ///        execution.
      /// @param[in] name Name of predicate this statement refers to.
      /// @param[in] val  Value this Action changes the predicate to.
      void addSet(PName name, PVal val);

      /// @brief Add a single predicate to the list that we unset after
      ///        execution.
      /// @param[in] pred Name of Predicate to add.
      void addClear(PName pred);

      /// @brief Get this Action's friendly name.
      /// @return This Action's name.
      const std::string& getName() const { return mName; }

      /// @brief Get the cost of using this Action.
      /// @return This Action's cost.
      float getCost() const { return mCost; }

      /// @brief Constructor with name.
      /// @param[in] name Friendly name for this Action.
      /// @param[in] cost Cost of performing this Action.
      Action(std::string name, float cost = 1.0f);

      /// @brief Default constructor.
      Action();
      /// @brief Default destructor.
      ~Action();

   protected:
   private:
      /// @brief Friendly name of this Action.
      std::string mName;
      /// @brief Cost of using this Action in a plan.
      float mCost;
      /// @brief Maps predicate names to the values we require for this Action
      ///        to be valid.
      worldrep mRequired;
      /// @brief Maps predicate names to the values they are set to after this
      ///        Action executes successfully.
      worldrep mPostSet;
      /// @brief List of predciates that are cleared (unset) after execution.
      pnamelist mPostClear;
   };

   /// @brief Knowledge about a state of the world, current or possible.
   class WorldState {
   public:
      /// @brief Is the predicate set to a value?
      /// @param[in] pred Name of the predicate to check.
      /// @return True iff the predicate is set to some valid value.
      bool predicateSet(PName pred) const;

      /// @brief Get the value of a predicate.
      /// @param[in] pred Name of predicate to check.
      /// @return The value of the predicate
      PVal getPredicate(PName pred) const;

      /// @brief Set the value of a predicate.
      /// @param[in] pred Name of predicate to set.
      /// @param[in] val Value to set the predicate to.
      void setPredicate(PName pred, PVal val);

      /// @brief Remove our knowledge of a certain predicate.
      /// @param[in] pred Name of the predicate to clear.
      void unsetPredicate(PName pred);

      /// @brief Do the given Action's pre-conditions match this world state?
      /// @param[in] ac Action instance to test against this world state.
      /// @return True iff the Action is valid under the current world state.
      bool actionPreMatch(const Action *ac) const;

      /// @brief Does the given Action, executed from an arbitrary world state,
      ///        result in this world state?
      /// @param[in] ac Action to compare.
      bool actionPostMatch(const Action *ac) const;

      /// @brief Apply the given Action to this WorldState in the forwards
      ///        direction.
      /// @param[in] ac Action to apply to the current state of the world.
      void applyActionForward(const Action *ac);

      /// @brief Remove the effects of the given Action from the world.
      /// @param[in] ac Action to remove from the current state.
      void applyActionReverse(const Action *ac);

      /// @brief Compare two world states.
      /// @param[in] ws1 First WorldState to compare.
      /// @param[in] ws2 Another WorldState to compare.
      /// @return Number of predicates that differ in value between states.
      static unsigned int comp(const WorldState &ws1, const WorldState &ws2);

      /// @brief Default constructor.
      WorldState();
      /// @brief Default destructor.
      ~WorldState();

      /// @brief Boolean equality test.
      /// This equality test will compare WorldStates based on their hash codes,
      /// providing a faster negative result. If their hash codes are equal, then
      /// WorldState::comp is used to verify.
      bool operator==(const WorldState &s) const
      { return mHash != s.mHash? false: !comp(*this, s); }

      /// @brief Boolean inequality test.
      bool operator!=(const WorldState &s) const
      { return !this->operator==(s); }

   protected:
   private:
      /// @brief Get the name of the world state entry.
      static inline PName getPName(worldrep::const_iterator it)
      { return it->first; }
      /// @brief Get the Predicate of the world state entry.
      static inline PVal getPVal(worldrep::const_iterator it)
      { return it->second; }
      /// @brief Internal representation of world state.
      worldrep mState;

      /// @brief Calculated hash value of this state.
      unsigned int mHash;
      /// @brief Update our hash value.
      void updateHash();

      /// @brief Internal method to set the value of a predicate.
      /// @param[in] pred Name of predicate to set.
      /// @param[in] val Value to set the predicate to.
      void _setPredicate(PName pred, PVal val);

      /// @brief Internal method to mark that a predicate is unset.
      /// @param[in] pred Name of the predicate to clear.
      void _unsetPredicate(PName pred);
   };

   /// @brief An interface used to log the planning process.
   /// Designed to be implemented by the end-user in a manner particular to
   /// their application and requirements.
   class AesopLogger {
   public:
      /// @brief Record an event taking place. Uses printf-like syntax for now.
      /// @param[in] fmt event format string.
      /// @todo Make this function more useful! Also, provide more fine-grained
      ///       logging. Possibly split over multiple methods.
      virtual void logEvent(const char *fmt, ...) = 0;
   protected:
   private:
   };

   /// @brief A Plan is a sequence of Actions that take us from one WorldState
   ///        to another.
   /// @todo Eventually this will be something like ActionEntry, accounting for
   ///       Actions that can be executed with different parameters. Also,
   ///       maybe deal with something other than copied values.
   typedef std::list<const Action*> Plan;

   /// @brief An ActionSet is a bunch of Actions that we are allowed to use.
   /// The pointers in this list are guaranteed to be non-NULL.
   /// @todo This list should take into account a preference for each Action.
   ///       So, certain ActionSets can prefer Actions over others, in addition
   ///       to considering the weights of the Actions themselves.
   typedef std::list<const Action*> ActionSet;

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
      /// @param[in] log Logger object to record the Planner's activity.
      /// @return True if the plan was successfully calculated, false if no
      ///         plan exists or something went wrong in the planning process.
      bool plan(AesopLogger *log = NULL);

      /// @brief Start a sliced plan.
      /// @param[in] log Logger object to record the Planner's activity.
      /// @return True if the plan was successfully initialised, false if
      ///         something went wrong in initialisation.
      bool initSlicedPlan(AesopLogger *log = NULL);

      /// @brief Update a sliced plan.
      /// @param[in] log Logger object to record the Planner's activity.
      /// @return False if a valid plan was not found; true otherwise.
      bool updateSlicedPlan(AesopLogger *log = NULL);

      /// @brief Output the result of a computed plan to 
      /// @param[in] log Logger object to record the Planner's activity.
      void finaliseSlicedPlan(AesopLogger *log = NULL);

      /// @brief US English spelling of finaliseSlicedPlan. 'Cause I'm a nice guy.
      /// @see Planner::finaliseSlicedPlan
      inline void finalizeSlicedPlan(AesopLogger *log = NULL)
      { finaliseSlicedPlan(log); }

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
   };
};

#endif
