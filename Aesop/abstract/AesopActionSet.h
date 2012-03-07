/// @file AesopActionSet.h
/// Definition of ActionSet interface class.

#ifndef _AE_ACTIONSET_H_
#define _AE_ACTIONSET_H_

#include <vector>
#include "AesopPredicates.h"
#include "AesopWorldState.h"
#include "AesopObjects.h"

namespace Aesop {
   /// A set of Actions defined in a particular planning problem.
   /// @ingroup Aesop
   class ActionSet {
   public:
      /// Identifier for an action.
      typedef unsigned int actionID;

      /// Do we have a specific action?
      /// @param[in] ac Look for actions with this identifier.
      /// @return True iff we have an action with that identifier.
      virtual bool has(actionID ac) const = 0;

      /// Get the number of actions defined.
      /// @return Number of user-defined actions.
      virtual unsigned int size() const = 0;

      /// @name Iteration
      /// @{

      /// Iterator over this set is simply an index.
      typedef actionID const_iterator;

      /// Iterator to beginning of actions.
      virtual const_iterator begin() const = 0;
      /// Iterator to end of actions.
      virtual const_iterator end() const = 0;

      /// @}

      /// @name WorldState manipulation
      /// @{

      /// A list of parameter lists represents all possible combinations
      ///        of parameters.
      typedef std::vector<WorldState::paramlist> paramcombos;

      /// Supply a list of all valid parameter combinations for an action.
      /// @param[in]  ac      Action to get parameters for.
      /// @param[out] list    List to add parameter lists to.
      /// @param[in]  objects Set of objects to choose from.
      virtual void getParamList(const_iterator ac, paramcombos &list, const Objects &objects) const = 0;

      /// Match an action's preconditions to a WorldState.
      /// @param[in] ac     Action to match.
      /// @param[in] params Parameters to the action.
      /// @param[in] ws     WorldState to check action against.
      /// @return True iff the action can be performed in the given WorldState.
      virtual bool preMatch(const_iterator ac, const WorldState::paramlist &params, const WorldState &ws) const = 0;

      /// Match an action's results to a WorldState.
      /// @param[in] ac     Action to match.
      /// @param[in] params Parameters to the action.
      /// @param[in] ws     WorldState to check action against.
      /// @return True iff executing the action could lead to the given WorldState.
      virtual bool postMatch(const_iterator ac, const WorldState::paramlist &params, const WorldState &ws) const = 0;

      /// Apply an action to a WorldState.
      /// @param[in] ac     Action to match.
      /// @param[in] params Parameters to the action.
      /// @param[in] ns     WorldState to apply changes to.
      virtual void applyForward(const_iterator ac, const WorldState::paramlist &params, WorldState &ns) const = 0;

      /// Apply an action in reverse to a WorldState.
      /// @param[in] ac     Action to match.
      /// @param[in] params Parameters to the action.
      /// @param[in] ws     WorldState to apply changes to.
      virtual void applyReverse(const_iterator ac, const WorldState::paramlist &params, WorldState &ns) const = 0;

      /// @}

      /// Return a string representation of the given action.
      /// @param[in] it Action to represent.
      /// @return A string that represents the given action.
      virtual std::string repr(const_iterator it) const = 0;

      /// Get our Predicates object.
      /// @return Handle of our Predicates.
      const Predicates &getPredicates() const { return mPredicates; }

      /// Default constructor.
      /// @param[in] preds Set of Predicates that define what our actions can do.
      ActionSet(const Predicates &p) : mPredicates(p) {}

   protected:
      /// Alternate name for has method.
      /// @see ActionSet::has
      bool have(actionID ac) const { return has(ac); }

   private:
      /// Predicates to validate Action parameters.
      const Predicates &mPredicates;
   };
};

#endif
