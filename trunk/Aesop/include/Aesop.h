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

#include "AesopConfig.h"

/// @namespace ae
/// @brief Includes all Aesop functions and classes.
namespace ae {
   /// @brief Represents the name of a predicate.
   typedef std::string PName;
   /// @brief Represents the value of a predicate.
   typedef unsigned char PVal;

   /// @brief A Predicate has a value and a set flag.
   ///
   /// A Predicate does not store its own name; this is done in WorldState and
   /// its internal map of PNames to Predicate instances.
   struct Predicate {
      PVal val;
      bool set;
      /// @brief Default constructor.
      Predicate()
      {
         val = 0;
         set = false;
      }
      /// @brief Value constructor.
      Predicate(PVal v, bool s)
      {
         val = v;
         set = s;
      }
   };

   /// @brief A name-value pair represents setting or checking the value of a
   ///        Predicate. Used by Action.
   struct Statement {
      PName name;
      PVal val;
      /// @brief Default constructor.
      Statement()
      {
         name = "";
         val = 0;
      }
      /// @brief Value constructor.
      Statement(PName n, PVal v)
      {
         name = n;
         val = v;
      }
   };

   /// @brief An atomic change that can be made to the world state.
   class Action {
   public:
      /// @brief Abstract the type of container used to store predicates.
      typedef std::list<Statement> statements;
      typedef std::list<PName> predicates;

      /// @brief Get the names of the statements that must be TRUE.
      const statements& getRequired() const { return mRequired; }
      /// @brief Get the names of statements we set to some value.
      const statements& getSet()      const { return mPostSet; }
      /// @brief Get the names of statements we UNSET.
      const predicates& getCleared()  const { return mPostClear; }

      /// @brief Add a single Statement to our list of required statements.
      /// @param[in] st Statement to add.
      void addRequired(const Statement st);
      /// @brief Add a list of Statements to our required set.
      /// @param[in] sts  A pointer to an array of Statements.
      /// @param[in] size Length of array.
      void addRequired(const Statement sts[], unsigned int size);

      /// @brief Add a single Statement to our list of Predicates to set after
      ///        execution.
      /// @param[in] st Statement to add.
      void addSet(const Statement st);
      /// @brief Add a list of Statements to our post-set list.
      /// @param[in] sts  A pointer to an array of Statements.
      /// @param[in] size Length of array.
      void addSet(const Statement sts[], unsigned int size);

      /// @brief Add a single Predicate to the list that we unset after
      ///        execution.
      /// @param[in] pred Name of Predicate to add.
      void addClear(const PName pred);
      /// @brief Add a list of Statements to our required set.
      /// @param[in] preds A pointer to an array of PNames.
      /// @param[in] size  Length of array.
      void addClear(const PName preds[], unsigned int size);

      /// @brief Get this Action's friendly name.
      /// @return This Action's name.
      const std::string& getName() const { return mName; }

      /// @brief Constructor with name.
      /// @param[in] name Friendly name for this Action.
      Action(std::string name);

      /// @brief Default constructor.
      Action();
      /// @brief Default destructor.
      ~Action();

   protected:
   private:
      /// @brief Friendly name of this Action.
      std::string mName;
      /// @brief 
      statements mRequired;
      /// @brief 
      statements mPostSet;
      /// @brief 
      predicates mPostClear;
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

      /// @brief mark that a predicate is unset.
      /// @param[in] pred Name of the predicate to clear.
      void unsetPredicate(PName pred);

      /// @brief Do the given Action's pre-conditions match this world state?
      /// @param[in] ac Action instance to test against this world state.
      /// @return True iff the Action is valid under the current world state.
      bool actionPreMatch(const Action *ac) const;

      /// @todo How does this method work?
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

   protected:
   private:
      /// @brief Abstract the representation of the world state.
      typedef std::map<PName, Predicate> worldrep;
      /// @brief Get the name of the world state entry.
      static inline PName getPName(worldrep::const_iterator it)
      { return it->first; }
      /// @brief Get the Predicate of the world state entry.
      static inline Predicate getPred(worldrep::const_iterator it)
      { return it->second; }

      /// @brief Internal representation of world state.
      worldrep mState;
   };

   /// @brief A Plan is a sequence of Actions that take us from one WorldState
   ///        to another.
   /// @todo Eventually this will be something like ActionEntry, accounting for
   ///       Actions that can be executed with different parameters.
   typedef std::list<Action> Plan;

   /// @brief An ActionSet is a bunch of Actions that we are allowed to use.
   typedef std::list<Action> ActionSet;

   /// @brief A context in which we can make plans.
   class Planner {
   public:
      /// @brief Set our starting WorldState.
      /// @param[in] start Pointer to a WorldState.
      void setStart(const WorldState *start);

      /// @brief Set our goal state.
      /// @param[in] goal Pointer to a WorldState.
      void setGoal(const WorldState *goal);

      /// @brief Create a plan!
      bool plan();

      /// @brief Get the currently constructed plan.
      /// @return A Plan.
      const Plan& getPlan() const;

      /// @brief Value constructor.
      /// @param[in] start Starting world state.
      /// @param[in] goal  Target world state.
      /// @param[in] set   ActionSet that defines the Actions we may perform.
      Planner(const WorldState *start, const WorldState *goal);

      /// @brief Default constructor.
      Planner();
      /// @brief Default destructor.
      ~Planner();

   protected:

   private:
      /// @brief Starting state.
      /// Not allowed to modify this.
      const WorldState *mStart;
      /// @brief Goal state.
      /// Not allowed to modify this.
      const WorldState *mGoal;
      /// @brief Current plan to get from mStart to mGoal.
      Plan mPlan;
      /// @brief Set of Actions we are allowed to perform.
      const ActionSet *mActions;
   };
};

#endif