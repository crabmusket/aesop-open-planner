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
   /// @addtogroup Aesop
   /// @{

   /// @brief Represents the name of a predicate.
   typedef unsigned int PName;
   /// @brief Represents the value of a predicate.
   typedef unsigned char PVal;
   /// @brief Method of storing predicates and their values.
   typedef std::map<PName, PVal> worldrep;
   /// @brief Simply stores a list of predicate names.
   typedef std::vector<PName> pnamelist;
   /// @brief Mapping of predicates to Action parameter indices.
   typedef std::map<PName, unsigned int> actionparams;
   /// @brief A list of parameter values specific to an ActionEntry.
   typedef std::vector<PVal> paramlist;
   /// @brief A set of paramlist objects used to evaluate a single Action with
   ///        many different parameter lists.
   typedef std::list<paramlist> paramset;

   /// @brief An interface used to log the planning process.
   /// Designed to be implemented by the end-user in a manner particular to
   /// their application and requirements.
   class Context {
   public:
      /// @brief Record an event taking place. Uses printf-like syntax for now.
      /// @param[in] fmt event format string.
      /// @todo Make this function more useful! Also, provide more fine-grained
      ///       logging. Possibly split over multiple methods.
      virtual void logEvent(const char *fmt, ...) = 0;
   protected:
   private:
   };

   /// @brief An atomic change that can be made to the world state.
   class Action {
   public:
      /// @brief Get predicate->value mapping that we require to be valid.
      const worldrep& getRequired() const { return mRequired; }
      /// @brief Get the predicate->value mapping we apply when executed.
      const worldrep& getSet()      const { return mPostSet; }
      /// @brief Get the names of statements we unset upon execution.
      const pnamelist& getCleared()  const { return mPostClear; }
      /// @brief Get the predicate->parameter mapping that we require.
      const actionparams& getRequiredParams() const { return mRequiredParam; }
      /// @brief Get the predicate->parameter mapping that we set.
      const actionparams& getSetParams() const {return mPostSetParam; }

      /// @brief Add a single statement to our list of required statements.
      /// @param[in] name Name of the predicate the statement refers to.
      /// @param[in] val  Value the predicate is required to take.
      void addRequired(PName name, PVal val);

      /// @brief Add a mapping between a predicate and a parameter.
      /// @param[in] name  Predicate name to map to a parameter.
      /// @param[in] param Index of a parameter to map to.
      void addRequiredParam(PName name, unsigned int param);

      /// @brief Add a single statement to our list of predicates to set after
      ///        execution.
      /// @param[in] name Name of predicate this statement refers to.
      /// @param[in] val  Value this Action changes the predicate to.
      void addSet(PName name, PVal val);

      /// @brief Add a mapping between a predicate and a parameter.
      /// @param[in] name  Predicate name to map to a parameter.
      /// @param[in] param Index of a parameter to map to.
      void addSetParam(PName name, unsigned int param);

      /// @brief Add a single predicate to the list that we unset after
      ///        execution.
      /// @param[in] pred Name of Predicate to add.
      void addClear(PName pred);

      /// @brief Fills in parameters this Action can take based on a given
      ///        starting set of parameters.
      /// @param[in]  ctx   A Context object to provide implementation-specific
      ///                   data and abilities.
      /// @param[in]  plist A single list of parameters that is required by a
      ///                   WorldState.
      /// @param[out] pset  A list of paramlist entries describing possible
      ///                   permutations of this Action's parameters, given
      ///                   the values in the starting set.
      virtual void getParams(Context *ctx, const paramlist &plist, paramset &pset) const { pset.clear(); }

      /// @brief Get this Action's friendly name.
      /// @return This Action's name.
      const std::string& getName() const { return mName; }

      /// @brief Get number of parameters.
      /// @return The number of parameters that define an instance of this
      ///         Action.
      unsigned int getNumParams() const { return mNumParams; };

      /// @brief Get the cost of using this Action.
      /// @return This Action's cost.
      float getCost() const { return mCost; }

      /// @brief Default constructor.
      /// @param[in] name   Friendly name for this Action.
      /// @param[in] params The number of variable parameters this Action has.
      /// @param[in] cost   Cost of performing this Action.
      Action(std::string name, float cost = 1.0f);

      /// @brief Default destructor.
      ~Action();

   protected:
      /// @brief Number of parameters we operate on.
      unsigned int mNumParams;

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
      /// @brief Maps predicate names to parameter indices which we require the
      ///        predicate to be set to.
      /// For example, if an entry in this map is ("at", 0) then for the Action
      /// to be valid, the "at" predicate must be set to the value of the 0th
      /// parameter to this Action.
      actionparams mRequiredParam;
      /// @brief Maps predicate names to parameter indices which should provide
      ///        values for them to be set to.
      /// For example, if an entry in this map is ("at", 1) then the "at"
      /// predicate will be set to whatever value is in this Action's 1st param
      /// when the Action executes.
      actionparams mPostSetParam;
   };

   /// @brief Represents an instance of an Action with a list of defined
   ///        parameter values.
   struct ActionEntry {
      /// @brief The Action this entry is an 'instance' of.
      const Action* ac;
      /// @brief Array of parameter values 
      paramlist params;

      /// @brief Default constructor.
      /// @param[in] a Action this ActionEntry is an instance of.
      ActionEntry()
      {
         ac = NULL;
      }
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

      /// @brief Set the appropriate values of set parameters.
      /// @param[in]  ac     Action that is being tested.
      /// @param[out] params List of parameter values that this world state
      ///                    requires.
      void actionGetParams(const Action *ac, paramlist &params) const;

      /// @brief Do the given Action's pre-conditions match this world state?
      /// @param[in] ac     Action instance to test against this world state.
      /// @param[in] params Parameters to the Action instance if it takes any.
      /// @return True iff the Action is valid under the current world state.
      bool actionPreMatch(const Action *ac, const paramlist *params = NULL) const;

      /// @brief Does the given Action, executed from an arbitrary world state,
      ///        result in this world state?
      /// @param[in]  ac     Action to compare.
      /// @param[out] params Parameters the Action must use for it to result in
      ///                    this world state.
      /// @return True iff the Action results in the current world state.
      bool actionPostMatch(const Action *ac, const paramlist *params = NULL) const;

      /// @brief Apply the given Action to this WorldState in the forwards
      ///        direction.
      /// @param[in] ac     Action to apply to the current state of the world.
      /// @param[in] params Parameters to the Action instance if it takes any.
      void applyActionForward(const Action *ac, const paramlist *params = NULL);

      /// @brief Remove the effects of the given Action from the world.
      /// @param[in] ac     Action to remove from the current state.
      /// @param[in] params Parameters to the Action instance if it takes any.
      void applyActionReverse(const Action *ac, const paramlist *params = NULL);

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

   /// @brief A Plan is a sequence of Actions that take us from one WorldState
   ///        to another.
   typedef std::list<ActionEntry> Plan;

   /// @brief An ActionSet is a bunch of Actions that we are allowed to use as
   ///        well as multipliers on their cost representing user preferences.
   class ActionSet {
   public:
      /// @brief Redefinition of std::map type as ActionSet.
      typedef std::map<const Action*, float> actionmap;

      /// @name STL
      /// @{
      typedef actionmap::const_iterator const_iterator;
      actionmap::const_iterator begin() const { return mActions.begin(); }
      actionmap::const_iterator end() const { return mActions.end(); }
      /// @}

      /// @brief Add an Action to this set with a given preference multiplier.
      void add(const Action* ac, float pref = 1.0f) { if(pref < 0.0f) pref = 0.0f; mActions[ac] = pref; }
      /// @brief Remove an Action from this set.
      void remove(const Action *ac) { mActions.erase(ac); }
   protected:
   private:
      /// @brief Store a map of Action pointers to preferences.
      actionmap mActions;
   };

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

   /// @}
};

#endif
