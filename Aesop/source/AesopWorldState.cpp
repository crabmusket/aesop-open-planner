/// @file AesopWorldState.cpp
/// @brief Implementation of WorldState class as defined in Aesop.h

#include "Aesop.h"

namespace ae {
   /// @class WorldState
   ///
   /// 

   WorldState::WorldState()
   {
   }

   WorldState::~WorldState()
   {
   }

   bool WorldState::predicateSet(PName pred) const
   {
      worldrep::const_iterator it = mState.find(pred);
      if(it == mState.end())
         return false;
      return it->second.set;
   }

   PVal WorldState::getPredicate(PName pred) const
   {
      worldrep::const_iterator it = mState.find(pred);
      if(it == mState.end())
         return 0;
      return it->second.val;
   }

   void WorldState::setPredicate(PName pred, PVal val)
   {
      mState[pred].val = val;
      mState[pred].set = true;
   }

   void WorldState::unsetPredicate(PName pred)
   {
      mState[pred].set = false;
   }

   /// For a 'pre-match' to be valid, we compare the Action's required and
   /// vetoed predicates to the values in the current world state. It must
   /// be the case that all 'required' predicates are flagged TRUE and all
   /// 'vetoed' predicates are flagged FALSE.
   bool WorldState::actionPreMatch(const Action *ac) const
   {
      const Action::statements &st = ac->getRequired();
      Action::statements::const_iterator it;

      for(it = st.begin(); it != st.end(); it++)
      {
         // If we don't have a mapping for this predicate then we fail.
         if(!predicateSet(it->name))
            return false;
         // If the predicate isn't set to the right value, we fail.
         if(getPredicate(it->name) != it->val)
            return false;
      }

      return true;
   }

   /// This method compares a desired world state with an action's results. In
   /// doing this, we match up 
   bool WorldState::actionPostMatch(const Action *ac) const
   {
      Action::statements::const_iterator sit;
      Action::predicates::const_iterator pit;

      // Check predicates that are set to true.
      const Action::statements &st = ac->getSet();
      for(sit = st.begin(); sit != st.end(); sit++)
      {
         // If we don't have a mapping for this predicate, we're still good.
         if(!predicateSet(sit->name))
            continue;
         // If the predicate isn't correct, we fail.
         if(getPredicate(sit->name) != sit->val)
            return false;
      }

      // Check predicates that should be unset.
      const Action::predicates &pr = ac->getCleared();
      for(pit = pr.begin(); pit != pr.end(); pit++)
      {
         // If we have a value for this predicate then we fail.
         if(predicateSet(*pit))
            return false;
      }

      return true;
   }

   /// Apply an Action to the current world state. The Action's effects are
   /// applied to the current set of predicates.
   void WorldState::applyActionForward(const Action *ac)
   {
      Action::statements::const_iterator sit;
      Action::predicates::const_iterator pit;

      // Predicates set to TRUE.
      const Action::statements &st = ac->getSet();
      for(sit = st.begin(); sit != st.end(); sit++)
         setPredicate(sit->name, sit->val);

      // Predicates UNSET.
      const Action::predicates &pr = ac->getCleared();
      for(pit = pr.begin(); pit != pr.end(); pit++)
         unsetPredicate(*pit);
   }

   /// This method applies an Action to a WorldState in reverse. In effect,
   /// it determines the state of the world required that when this Action is
   /// applied to it, the result is the current state.
   /// This involves making sure that the new state's predicates match the
   /// Action's prerequisites, and clearing any predicates that the Action
   /// sets.
   void WorldState::applyActionReverse(const Action *ac)
   {
      Action::statements::const_iterator sit;
      Action::predicates::const_iterator pit;

      // Predicates that must be some value.
      const Action::statements &req = ac->getRequired();
      for(sit = req.begin(); sit != req.end(); sit++)
         setPredicate(sit->name, sit->val);

      // Predicates that are touched by the Action are unset.
      const Action::statements &set = ac->getSet();
      for(sit = set.begin(); sit != set.end(); sit++)
         unsetPredicate(sit->name);
      const Action::predicates &pr = ac->getCleared();
      for(pit = pr.begin(); pit != pr.end(); pit++)
         unsetPredicate(*pit);
   }

   /// The difference score between two WorldStates is equal to the number of
   /// predicates which they both have defined, but to different values.
   /// Predicates that are not defined in either state, or are flagged as unset
   /// in either, are not considered.
   unsigned int WorldState::comp(const WorldState &ws1, const WorldState &ws2)
   {
      int score = 0;

      // Iterators run from lowest to highest key values.
      worldrep::const_iterator p1 = ws1.mState.begin();
      worldrep::const_iterator p2 = ws2.mState.begin();

      while(p1 != ws1.mState.end() && p2 != ws2.mState.end())
      {
         // Compare names of predicates (keys).
         int cmp = getPName(p1).compare(getPName(p2));
         if(cmp == 0)
         {
            // Names are equal. Check for different values.
            if(getPred(p1).set && getPred(p2).set &&
               getPred(p1).val != getPred(p2).val)
               score++;
            p1++;
            p2++;
         }
         else if(cmp > 0)
         {
            // Key 1 is greater.
            p2++;
         }
         else if(cmp < 0)
         {
            // Key 2 is greater.
            p1++;
         }
      }

      return score;
   }
};
