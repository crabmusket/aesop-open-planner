/// @file AesopSimpleActionSet.h
/// Definition of SimpleActionSet class.

#ifndef _AE_SIMPLE_ACTIONSET_H_
#define _AE_SIMPLE_ACTIONSET_H_

#include <vector>
#include "abstract/AesopActionSet.h"

namespace Aesop {
   /// A very simple ActionSet that does not allow actions to use
   ///        parameters.
   /// @ingroup Aesop
   class SimpleActionSet : public ActionSet {
   public:
      /// @name Action creation
      /// @{

      /// Create a new action.
      /// @param[in] name Name of the new action to create.
      /// @return This object.
      SimpleActionSet &create(std::string name);

      /// Add a precondition to the action under construction.
      /// @param[in] cond The ID of the predicate that must be set to allow
      ///                 this action.
      /// @param[in] set  Whether the predicate must be set or unset.
      /// @return This object.
      SimpleActionSet &condition(Predicates::predID cond, bool set);

      /// Add an effect to the action under construction.
      /// @param[in] eff The ID of the predicate this action affects.
      /// @param[in] set Whether to set or unset this predicate.
      /// @return This object.
      SimpleActionSet &effect(Predicates::predID cond, bool set);

      /// Set the cost of the action we're constructing.
      /// @param[in] cost Cost of the new action.
      /// @return This object.
      SimpleActionSet &cost(float cost);

      /// Add the action that is currently being constructed.
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

      /// Default constructor.
      SimpleActionSet(const Predicates &p);

      /// Default destructor.
      ~SimpleActionSet();

   protected:
   private:
      /// Stores the details of a GOAP action.
      struct SimpleAction {
         /// Three possibilities for a predicate: we want it to be false,
         ///        want it to be true, or we don't care what value it has.
         enum settype {
            Unset,
            Set,
            None
         };

         /// Represents the conditions and effects applied to a single
         ///        predicate.
         struct predicate {
            Predicates::predID pred;
            settype cond;
            settype eff;
            predicate() : pred(0), cond(None), eff(None) {}
         };

         /// Human-readable identifier for this action.
         std::string name;
         /// Cost to perform this action.
         float cost;

         /// Store predicates as a simple list.
         typedef std::vector<predicate> predslist;
         /// List of instuctions about predicates.
         predslist predicates;

         /// Default constructor.
         SimpleAction() : name(""), cost(0.0f) {}
      };

      /// The action under construction.
      SimpleAction mCurrAction;

      /// Store actions in a vector.
      typedef std::vector<SimpleAction> actionlist;
      /// All actions that have been defined.
      actionlist mActions;
   };
};

#endif
