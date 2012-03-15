/// @file Aesop.h
/// @brief Main file for Aesop open planning library.

#ifndef _AE_WORLDSTATE_H_
#define _AE_WORLDSTATE_H_

#include "AesopTypes.h"
#include "AesopAction.h"

namespace Aesop {
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
};

#endif
