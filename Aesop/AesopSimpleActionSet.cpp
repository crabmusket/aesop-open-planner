/// @file AesopSimpleActionSet.cpp
/// Implementation of SimpleActionSet class as defined in AesopSimpleActionSet.h

#include <algorithm>
#include "AesopSimpleActionSet.h"

namespace Aesop {
   /// @class SimpleActionSet
   ///
   /// 

   SimpleActionSet::SimpleActionSet(const Predicates &p)
      : ActionSet(p)
   {
   }

   SimpleActionSet::~SimpleActionSet()
   {
   }

   SimpleActionSet &SimpleActionSet::create(std::string name)
   {
      mCurrAction = SimpleAction();
      mCurrAction.name = name;
      return *this;
   }

   SimpleActionSet &SimpleActionSet::condition(Predicates::predID cond, bool set)
   {
      SimpleAction::predslist::iterator it;
      for(it = mCurrAction.predicates.begin(); it != mCurrAction.predicates.end(); it++)
      {
         if(it->pred == cond)
         {
            it->cond = (SimpleAction::settype)set;
            return *this;
         }
      }
      mCurrAction.predicates.push_back(SimpleAction::predicate());
      mCurrAction.predicates.back().pred = cond;
      mCurrAction.predicates.back().cond = (SimpleAction::settype)set;
      return *this;
   }

   SimpleActionSet &SimpleActionSet::effect(Predicates::predID eff, bool set)
   {
      SimpleAction::predslist::iterator it;
      for(it = mCurrAction.predicates.begin(); it != mCurrAction.predicates.end(); it++)
      {
         if(it->pred == eff)
         {
            it->eff = (SimpleAction::settype)set;
            return *this;
         }
      }
      mCurrAction.predicates.push_back(SimpleAction::predicate());
      mCurrAction.predicates.back().pred = eff;
      mCurrAction.predicates.back().eff = (SimpleAction::settype)set;
      return *this;
   }

   SimpleActionSet &SimpleActionSet::cost(float cost)
   {
      if(cost > 0.0f)
         mCurrAction.cost = cost;
      else
         mCurrAction.cost = 0.0f;
      return *this;
   }

   void SimpleActionSet::add()
   {
      mActions.push_back(mCurrAction);
   }

   bool SimpleActionSet::has(actionID ac) const
   {
      return ac < mActions.size();
   }

   void SimpleActionSet::getParamList(const_iterator ac, paramcombos &list, const Objects &objects) const
   {
      list.clear();
      list.push_back(WorldState::paramlist());
   }

   bool SimpleActionSet::preMatch(const_iterator ac, const WorldState::paramlist &params, const WorldState &state) const
   {
      const SimpleAction &action = mActions[ac];
      SimpleAction::predslist::const_iterator it;
      for(it = action.predicates.begin(); it != action.predicates.end(); it++)
      {
         // If we do not have a condition for this predicate, ignore.
         if(it->cond == SimpleAction::None)
            continue;
         // Make sure that predicate is in correct state.
         if((int)state.isSet(it->pred, WorldState::paramlist()) != it->cond)
            return false;
      }
      // No objections.
      return true;
   }

   bool SimpleActionSet::postMatch(const_iterator ac, const WorldState::paramlist &params, const WorldState &state) const
   {
      const SimpleAction &action = mActions[ac];
      SimpleAction::predslist::const_iterator it;
      for(it = action.predicates.begin(); it != action.predicates.end(); it++)
      {
         // If we do not have an effect for this predicate, don't worry about it.
         if(it->eff == SimpleAction::None)
            continue;
         // Make sure that predicate is in correct state.
         else if((int)state.isSet(it->pred, WorldState::paramlist()) != it->eff)
            return false;
      }
      // No objections.
      return true;
   }

   void SimpleActionSet::applyForward(const_iterator ac, const WorldState::paramlist &params, WorldState &ns) const
   {
      const SimpleAction &action = mActions[ac];
      SimpleAction::predslist::const_iterator it;
      for(it = action.predicates.begin(); it != action.predicates.end(); it++)
      {
         if(it->eff == SimpleAction::Set)
            ns.set(it->pred, WorldState::paramlist());
         else if(it->eff == SimpleAction::Unset)
            ns.unset(it->pred, WorldState::paramlist());
      }
   }

   void SimpleActionSet::applyReverse(const_iterator ac, const WorldState::paramlist &params, WorldState &ns) const
   {
      const SimpleAction &action = mActions[ac];
      SimpleAction::predslist::const_iterator it;
      for(it = action.predicates.begin(); it != action.predicates.end(); it++)
      {
         if(it->cond == SimpleAction::Set)
            ns.set(it->pred, WorldState::paramlist());
         else if(it->cond == SimpleAction::Unset)
            ns.unset(it->pred, WorldState::paramlist());
      }
   }
};
