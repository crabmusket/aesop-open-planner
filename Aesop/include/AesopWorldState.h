/// @file Aesop.h
/// Main file for Aesop open planning library.

#ifndef _AE_WORLDSTATE_H_
#define _AE_WORLDSTATE_H_

#include "AesopTypes.h"
#include "AesopAction.h"

namespace Aesop {
   /// Knowledge about a state of the world, current or possible.
   class WorldState {
   public:
      /// Is the predicate set to a value?
      /// @param[in] pred Name of the predicate to check.
      /// @return True iff the predicate is set to some valid value.
      bool predicateSet(PName pred) const;

      /// Get the value of a predicate.
      /// @param[in] pred Name of predicate to check.
      /// @return The value of the predicate
      PVal getPredicate(PName pred) const;

      /// Set the value of a predicate.
      /// @param[in] pred Name of predicate to set.
      /// @param[in] val Value to set the predicate to.
      void setPredicate(PName pred, PVal val);

      /// Remove our knowledge of a certain predicate.
      /// @param[in] pred Name of the predicate to clear.
      void unsetPredicate(PName pred);

      /// Set the appropriate values of set parameters.
      /// @param[in]  ac     Action that is being tested.
      /// @param[out] params List of parameter values that this world state
      ///                    requires.
      void actionGetParams(const Action *ac, paramlist &params) const;

      /// Do the given Action's pre-conditions match this world state?
      /// @param[in] ac     Action instance to test against this world state.
      /// @param[in] params Parameters to the Action instance if it takes any.
      /// @return True iff the Action is valid under the current world state.
      bool actionPreMatch(const Action *ac, const paramlist *params = NULL) const;

      /// Does the given Action, executed from an arbitrary world state,
      ///        result in this world state?
      /// @param[in]  ac     Action to compare.
      /// @param[out] params Parameters the Action must use for it to result in
      ///                    this world state.
      /// @return True iff the Action results in the current world state.
      bool actionPostMatch(const Action *ac, const paramlist *params = NULL) const;

      /// Apply the given Action to this WorldState in the forwards
      ///        direction.
      /// @param[in] ac     Action to apply to the current state of the world.
      /// @param[in] params Parameters to the Action instance if it takes any.
      void applyActionForward(const Action *ac, const paramlist *params = NULL);

      /// Remove the effects of the given Action from the world.
      /// @param[in] ac     Action to remove from the current state.
      /// @param[in] params Parameters to the Action instance if it takes any.
      void applyActionReverse(const Action *ac, const paramlist *params = NULL);

      /// Compare two world states.
      /// @param[in] ws1 First WorldState to compare.
      /// @param[in] ws2 Another WorldState to compare.
      /// @return Number of predicates that differ in value between states.
      static unsigned int comp(const WorldState &ws1, const WorldState &ws2);

      /// Default constructor.
      WorldState();
      /// Default destructor.
      ~WorldState();

      /// Boolean equality test.
      /// This equality test will compare WorldStates based on their hash codes,
      /// providing a faster negative result. If their hash codes are equal, then
      /// WorldState::comp is used to verify.
      bool operator==(const WorldState &s) const
      { return mHash != s.mHash? false: !comp(*this, s); }

      /// Boolean inequality test.
      bool operator!=(const WorldState &s) const
      { return !this->operator==(s); }

   protected:
   private:
      /// Get the name of the world state entry.
      static inline PName getPName(worldrep::const_iterator it)
      { return it->first; }
      /// Get the Predicate of the world state entry.
      static inline PVal getPVal(worldrep::const_iterator it)
      { return it->second; }
      /// Internal representation of world state.
      worldrep mState;

      /// Calculated hash value of this state.
      unsigned int mHash;
      /// Update our hash value.
      void updateHash();

      /// Internal method to set the value of a predicate.
      /// @param[in] pred Name of predicate to set.
      /// @param[in] val Value to set the predicate to.
      void _setPredicate(PName pred, PVal val);

      /// Internal method to mark that a predicate is unset.
      /// @param[in] pred Name of the predicate to clear.
      void _unsetPredicate(PName pred);
   };
};

#endif
