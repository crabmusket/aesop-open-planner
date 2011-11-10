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

#ifndef AE_PREDICATE_NAME_LEN
#define AE_PREDICATE_NAME_LEN 32
#endif

/// @namespace ae
/// @brief Includes all Aesop functions and classes.
namespace ae {
   /// Represents the name of a predicate.
   typedef std::string PName;
   /// Represents the value of a predicate.
   typedef unsigned char PVal;
   /// A predicate has a value and a set flag. It does not store its own name.
   struct Predicate {
      PVal val;
      bool set;
   };
   /// A name-value pair represents setting or checking the value of a
   /// Predicate. Used by Action.
   struct Statement {
      PName name;
      PVal val;
   };

   /// Boolean values for Predicates.
   enum PVals {
      FALSE,
      TRUE,
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

      /// @brief Default constructor.
      Action();
      /// @brief Default destructor.
      ~Action();
   protected:
   private:
      statements mRequired;
      statements mPostSet;
      predicates mPostClear;

      /// Preconditions. Each predicate in this list must be set to TRUE for
      /// this Action to be valid.

      /// Vetos. None of the predicates in this list may be TRUE for this
      /// Action to be valid.

      /// Post-set. After this Action is executed, it is expected that the
      /// predicates in this list take the value of TRUE.

      /// Post-unset. After this Action is executed, we expect that the
      /// predicates in this list become FALSE.

      /// Parametric requirements. For this Action to be valid, all of the
      /// predicates in each parameter list must be set to the value specified
      /// in the matching parameter.
      ///
      /// For example, if paramReq[0] = {location} and this Action instance's
      /// first (0th) parameter is "livingRoom", the predicate 'location' must
      /// include "livingRoom".

      /// Parametric results. After the Action is executed, the predicates in
      /// each parameter list will be set to the values of the matching
      /// parameters of the Action.
      ///
      /// For example, if paramSet[1] = {have} and this Action instance's
      /// second (1th) parameter is "bananas", then after the Action executes,
      /// the predicate 'have' will include "bananas".
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
      /// @see Action
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
      static inline PName getPName(worldrep::const_iterator it) { return it->first; }
      /// @brief Get the Predicate of the world state entry.
      static inline Predicate getPred(worldrep::const_iterator it) { return it->second; }

      /// @brief Internal representation of world state.
      worldrep mState;
   };
};

#endif
