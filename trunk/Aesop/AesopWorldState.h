/// @file AesopWorldState.h
/// @brief Definition of WorldState interface class.

#ifndef _AE_WORLDSTATE_H_
#define _AE_WORLDSTATE_H_

#include <vector>
#include "AesopPredicates.h"
#include "AesopObjects.h"

namespace Aesop {
   /// @brief Knowledge about a state of the world, current or possible.
   ///
   /// This class represents a set of knowledge (facts, or predicates) about
   /// the state of the world that we are planning within. A WorldState can be
   /// used by individual characters as a representation of their knowledge,
   /// but is also used internally in planning.
   ///
   /// @ingroup Aesop
   class WorldState {
   public:
      typedef std::vector<Objects::objectID> paramlist;

      /// @brief Is the predicate set?
      /// @param[in] pred   Name of the predicate to check.
      /// @param[in] params List of parameter values to check.
      /// @return True iff the predicate is set with the given parameters.
      virtual bool isSet(Predicates::predID pred, const paramlist &params) const = 0;

      /// @brief Is the predicate unset?
      /// In some types of worlds, being unset is not necessarily the opposite
      /// of being set.
      /// @param[in] pred   Name of the predicate to check.
      /// @param[in] params List of parameter values to check.
      /// @return True iff the predicate is unset with the given parameters.
      virtual bool isUnset(Predicates::predID pred, const paramlist &params) const = 0;

      /// @brief Set a predicate with specific parameters.
      /// @param[in] pred   Name of predicate to set.
      /// @param[in] params Map of parameter names to values to check.
      virtual void set(Predicates::predID pred, const paramlist &params) = 0;

      /// @brief Unset a predicate with specific paramaters.
      /// @param[in] pred   Name of the predicate to clear.
      /// @param[in] params Map of parameter names to values to check.
      virtual void unset(Predicates::predID pred, const paramlist &params) = 0;

      /// @brief Make a copy of this WorldState.
      /// @return A pointer to a new WorldState of the same class as this one,
      ///         initialised to the same value.
      virtual WorldState *clone() const = 0;

      /// @brief Get a string representation of this WorldState.
      /// @return A string representing this state.
      virtual std::string repr() const = 0;

      /// @brief Quantify the difference betweeh this WorldState and another.
      /// @param[in] other The WorldState to compare with.
      /// @return A numerical representation of the differences between these
      ///         states.
      virtual unsigned int compare(const WorldState &other) const = 0;

      virtual bool operator==(const WorldState &other) const = 0;
      virtual bool operator!=(const WorldState &other) const = 0;

      /// @brief Get the Predicates object used by this WorldState.
      /// @return A Predicates object.
      const Predicates &getPredicates() const { return mPredicates; }

      /// @brief Default constructor.
      /// @param[in] p Predicates object to validate our state.
      WorldState(const Predicates &p) : mPredicates(p) {}

   protected:
   private:
      /// @brief Handle to our Predicates object.
      const Predicates &mPredicates;
   };
};

#endif
