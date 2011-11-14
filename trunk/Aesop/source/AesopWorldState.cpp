/// @file AesopWorldState.cpp
/// @brief Implementation of WorldState class as defined in Aesop.h

#include <algorithm>

#include "Aesop.h"

namespace ae {
   /// @class WorldState
   ///
   /// This class represents a set of knowledge (facts, or predicates) about
   /// the state of the world that we are planning within. A WorldState can be
   /// used by individual characters as a representation of their knowledge,
   /// but is also used internally in planning.

   WorldState::WorldState()
   {
      mHash = 0;
   }

   WorldState::~WorldState()
   {
   }

   bool WorldState::predicateSet(PName pred) const
   {
      worldrep::const_iterator it = mState.find(pred);
      return it == mState.end();
   }

   PVal WorldState::getPredicate(PName pred) const
   {
      worldrep::const_iterator it = mState.find(pred);
      if(it == mState.end())
         return 0;
      return getPVal(it);
   }

   void WorldState::setPredicate(PName pred, PVal val)
   {
      mState[pred] = val;
      updateHash();
   }

   void WorldState::unsetPredicate(PName pred)
   {
      worldrep::iterator it = mState.find(pred);
      if(it != mState.end())
         mState.erase(it);
      updateHash();
   }

   /// For a 'pre-match' to be valid, we compare the Action's required
   /// predicates to the values in the current world state. All values must
   /// match for the Action to be valid.
   bool WorldState::actionPreMatch(const Action *ac) const
   {
      const worldrep &awr = ac->getRequired();
      worldrep::const_iterator it;

      for(it = awr.begin(); it != awr.end(); it++)
      {
         // If we don't have a mapping for this predicate then we fail.
         if(!predicateSet(getPName(it)))
            return false;
         // If the predicate isn't set to the right value, we fail.
         if(getPredicate(getPName(it)) != getPVal(it))
            return false;
      }

      return true;
   }

   /// This method compares a desired world state with an action's results. The
   /// comparison returns true if each predicate in our current state is either
   /// set by the Action, or required by it and not changed.
   bool WorldState::actionPostMatch(const Action *ac) const
   {
      worldrep::const_iterator it;
      worldrep::const_iterator ait;
      worldrep::const_iterator rit;

      const worldrep &set = ac->getSet();
      const worldrep &req = ac->getRequired();

      unsigned int matched = 0;

      for(it = mState.begin(); it != mState.end(); it++)
      {
         ait = set.find(getPName(it));
         if(ait == set.end())
         {
            // Action does not set this predicate. Does it require it?
            rit = req.find(getPName(it));
            if(rit == req.end())
               // Nope. We're fine, and this prerequisite will carry over.
               continue;
            else if(getPVal(rit) != getPVal(it))
               // Value is incorrect; bail!
               return false;
            else
               matched++;
         }
         else
         {
            // Action sets this predicate. Make sure value is correct.
            if(getPVal(ait) != getPVal(it))
               return false;
            else
               matched++;
         }
      }

      return matched != 0;
   }

   /// Apply an Action to the current world state. The Action's effects are
   /// applied to the current set of predicates.
   void WorldState::applyActionForward(const Action *ac)
   {
      worldrep::const_iterator sit;
      pnamelist::const_iterator pit;

      // Predicates set to TRUE.
      const worldrep &st = ac->getSet();
      for(sit = st.begin(); sit != st.end(); sit++)
         setPredicate(getPName(sit), getPVal(sit));

      // Predicates UNSET.
      const pnamelist &pr = ac->getCleared();
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
      worldrep::const_iterator sit;
      pnamelist::const_iterator pit;

      // Predicates that are touched by the Action are unset.
      const worldrep &set = ac->getSet();
      for(sit = set.begin(); sit != set.end(); sit++)
         unsetPredicate(getPName(sit));
      const pnamelist &pr = ac->getCleared();
      for(pit = pr.begin(); pit != pr.end(); pit++)
         unsetPredicate(*pit);

      // Predicates that must be some value. This may re-set some of the
      // predicates that were unset above.
      const worldrep &req = ac->getRequired();
      for(sit = req.begin(); sit != req.end(); sit++)
         setPredicate(getPName(sit), getPVal(sit));
   }

   /// This hash method sums the string hashes of all the predicate names in
   /// this state, XORing certain bits based on the values of each predicate.
   void WorldState::updateHash()
   {
      mHash = 0;
      worldrep::const_iterator it;
      for(it = mState.begin(); it != mState.end(); it++)
      {
         unsigned int l = getPName(it).length();
         while(l)
            mHash = 31 * mHash + getPName(it)[--l];
         mHash ^= getPVal(it) << getPName(it).length() % (sizeof(unsigned int) - sizeof(PVal));
      }
   }

   /// The difference score between two WorldStates is equal to the number of
   /// predicates which they both have defined, but to different values.
   /// Predicates that are not defined in one state, or are flagged as unset
   /// in either, are not considered.
   unsigned int WorldState::comp(const WorldState &ws1, const WorldState &ws2)
   {
      int score = 0;

      // Iterators run from lowest to highest key values.
      worldrep::const_iterator p1 = ws1.mState.begin();
      worldrep::const_iterator p2 = ws2.mState.begin();

      while(p1 != ws1.mState.end() || p2 != ws2.mState.end())
      {
         // One state may have run out of keys.
         if(p1 == ws1.mState.end())
         {
            score++;
            p2++;
            continue;
         }
         if(p2 == ws2.mState.end())
         {
            score++;
            p1++;
            continue;
         }

         // Compare names of predicates (keys).
         int cmp = getPName(p1).compare(getPName(p2));
         if(cmp == 0)
         {
            // Names are equal. Check for different values.
            if(getPVal(p1) != getPVal(p2))
               score++;
            p1++;
            p2++;
         }
         else if(cmp > 0)
         {
            // Key 1 is greater.
            score++;
            p2++;
         }
         else // if(cmp < 0)
         {
            // Key 2 is greater.
            score++;
            p1++;
         }
      }

      return score;
   }
};
