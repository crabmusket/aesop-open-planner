/// @file AesopActionSet.h
/// @brief Definition of ActionSet class.

#ifndef _AE_ACTIONSET_H_
#define _AE_ACTIONSET_H_

#include <vector>
#include "AesopPredicates.h"
#include "AesopWorldState.h"
#include "AesopObjects.h"

namespace Aesop {
   /// @brief A set of Actions defined in a particular planning problem.
   /// @ingroup Aesop
   class ActionSet {
   public:
      /// @brief Identifier for an action.
      typedef unsigned int actionID;

      /// @brief Do we have a specific action?
      /// @param[in] ac Look for actions with this identifier.
      /// @return True iff we have an action with that identifier.
      virtual bool has(actionID ac) const = 0;

      /// @brief Get the number of actions defined.
      /// @return Number of user-defined actions.
      virtual unsigned int size() const = 0;

      /// @name Iteration
      /// @{

      /// @brief Iterator over this set is simply an index.
      typedef actionID const_iterator;

      /// @brief Iterator to beginning of actions.
      virtual const_iterator begin() const = 0;
      /// @brief Iterator to end of actions.
      virtual const_iterator end() const = 0;

      /// @}

      /// @name WorldState manipulation
      /// @{

      /// @brief A list of parameter lists represents all possible combinations
      ///        of parameters.
      typedef std::vector<WorldState::paramlist> paramcombos;

      /// @brief Supply a list of all valid parameter combinations for an action.
      /// @param[in]  ac      Action to get parameters for.
      /// @param[out] list    List to add parameter lists to.
      /// @param[in]  objects Set of objects to choose from.
      virtual void getParamList(const_iterator ac, paramcombos &list, const Objects &objects) const = 0;

      /// @brief Match an action's preconditions to a WorldState.
      /// @param[in] ac     Action to match.
      /// @param[in] params Parameters to the action.
      /// @param[in] ws     WorldState to check action against.
      /// @return True iff the action can be performed in the given WorldState.
      virtual bool preMatch(const_iterator ac, const WorldState::paramlist &params, const WorldState &ws) const = 0;

      /// @brief Match an action's results to a WorldState.
      /// @param[in] ac     Action to match.
      /// @param[in] params Parameters to the action.
      /// @param[in] ws     WorldState to check action against.
      /// @return True iff executing the action could lead to the given WorldState.
      virtual bool postMatch(const_iterator ac, const WorldState::paramlist &params, const WorldState &ws) const = 0;

      /// @brief Apply an action to a WorldState.
      /// @param[in] ac     Action to match.
      /// @param[in] params Parameters to the action.
      /// @param[in] ns     WorldState to apply changes to.
      virtual void applyForward(const_iterator ac, const WorldState::paramlist &params, WorldState &ns) const = 0;

      /// @brief Apply an action in reverse to a WorldState.
      /// @param[in] ac     Action to match.
      /// @param[in] params Parameters to the action.
      /// @param[in] ws     WorldState to apply changes to.
      virtual void applyReverse(const_iterator ac, const WorldState::paramlist &params, WorldState &ns) const = 0;

      /// @}

      /// @brief Return a string representation of the given action.
      /// @param[in] it Action to represent.
      /// @return A string that represents the given action.
      virtual std::string repr(const_iterator it) const = 0;

      /// @brief Get our Predicates object.
      /// @return Handle of our Predicates.
      const Predicates &getPredicates() const { return mPredicates; }

      /// @brief Default constructor.
      /// @param[in] preds Set of Predicates that define what our actions can do.
      ActionSet(const Predicates &p) : mPredicates(p) {}

   protected:
      /// @brief Alternate name for has method.
      /// @see ActionSet::has
      bool have(actionID ac) const { return has(ac); }

   private:
      /// @brief Predicates to validate Action parameters.
      const Predicates &mPredicates;
   };

   /// @brief A very simple ActionSet that does not allow actions to use
   ///        parameters.
   /// @ingroup Aesop
   class SimpleActionSet : public ActionSet {
   public:
      /// @name Action creation
      /// @{

      /// @brief Create a new action.
      /// @param[in] name Name of the new action to create.
      /// @return This object.
      SimpleActionSet &create(std::string name);

      /// @brief Add a precondition to the action under construction.
      /// @param[in] cond The ID of the predicate that must be set to allow
      ///                 this action.
      /// @param[in] set  Whether the predicate must be set or unset.
      /// @return This object.
      SimpleActionSet &condition(Predicates::predID cond, bool set);

      /// @brief Add an effect to the action under construction.
      /// @param[in] eff The ID of the predicate this action affects.
      /// @param[in] set Whether to set or unset this predicate.
      /// @return This object.
      SimpleActionSet &effect(Predicates::predID cond, bool set);

      /// @brief Set the cost of the action we're constructing.
      /// @param[in] cost Cost of the new action.
      /// @return This object.
      SimpleActionSet &cost(float cost);

      /// @brief Add the action that is currently being constructed.
      void add();

      /// @}

      /// @name ActionSet
      /// @{

      virtual unsigned int size() const { return mActions.size(); }

      virtual const_iterator begin() const { return 0; }
      virtual const_iterator end() const { return size(); }

      virtual void getParamList(const_iterator it, paramcombos &list, const Objects &objects) const;

      virtual bool preMatch(const_iterator ac, const WorldState::paramlist &params, const WorldState &ws) const;
      virtual bool postMatch(const_iterator ac, const WorldState::paramlist &params, const WorldState &ws) const;
      virtual void applyForward(const_iterator ac, const WorldState::paramlist &params, WorldState &ns) const;
      virtual void applyReverse(const_iterator ac, const WorldState::paramlist &params, WorldState &ns) const;

      bool has(actionID ac) const;

      virtual std::string repr(const_iterator it) const { return mActions[it].name; }

      /// @}

      /// @brief Default constructor.
      SimpleActionSet(const Predicates &p);

      /// @brief Default destructor.
      ~SimpleActionSet();

   protected:
   private:
      /// @brief Stores the details of a GOAP action.
      struct SimpleAction {
         /// @brief Three possibilities for a predicate: we want it to be false,
         ///        want it to be true, or we don't care what value it has.
         enum settype {
            Unset,
            Set,
            None
         };

         /// @brief Represents the conditions and effects applied to a single
         ///        predicate.
         struct predicate {
            Predicates::predID pred;
            settype cond;
            settype eff;
            predicate() : pred(0), cond(None), eff(None) {}
         };

         /// @brief Human-readable identifier for this action.
         std::string name;
         /// @brief Cost to perform this action.
         float cost;

         /// @brief Store predicates as a simple list.
         typedef std::vector<predicate> predslist;
         /// @brief List of instuctions about predicates.
         predslist predicates;

         /// @brief Default constructor.
         SimpleAction() : name(""), cost(0.0f) {}
      };

      /// @brief The action under construction.
      SimpleAction mCurrAction;

      /// @brief Store actions in a vector.
      typedef std::vector<SimpleAction> actionlist;
      /// @brief All actions that have been defined.
      actionlist mActions;
   };
};

#endif
