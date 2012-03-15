/// @file AesopWorldState.cpp
/// @brief Implementation of WorldState class as defined in AesopWorldState.h

#include "AesopWorldState.h"

#include <algorithm>

namespace Aesop {
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
      return it != mState.end();
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
      _setPredicate(pred, val);
      updateHash();
   }

   void WorldState::_setPredicate(PName pred, PVal val)
   {
      mState[pred] = val;
   }

   void WorldState::unsetPredicate(PName pred)
   {
      _unsetPredicate(pred);
      updateHash();
   }

   void WorldState::_unsetPredicate(PName pred)
   {
      worldrep::iterator it = mState.find(pred);
      if(it != mState.end())
         mState.erase(it);
   }

   /// This method is responsible for setting the parameters in the paramlist
   /// that are required to be a certain value in order to match this state.
   void WorldState::actionGetParams(const Action *ac, paramlist &params) const
   {
      params.resize(ac->getNumParams());

      // Each parameter that sets a predicate must have the correct value.
      const actionparams &spl = ac->getSetParams();
      actionparams::const_iterator sit;
      for(sit = spl.begin(); sit != spl.end(); sit++)
         params[sit->second] = getPredicate(sit->first);

      // Each predicate required and not set must have the correct value.
      const actionparams &rpl = ac->getRequiredParams();
      actionparams::const_iterator rit;
      for(rit = rpl.begin(); rit != rpl.end(); rit++)
      {
         const worldrep &set = ac->getSet();
         if(set.find(rit->first) == set.end() &&
            spl.find(rit->first) == spl.end())
            params[rit->second] = getPredicate(rit->first);
      }
   }

   /// For a 'pre-match' to be valid, we compare the Action's required
   /// predicates to the values in the current world state. All values must
   /// match for the Action to be valid.
   bool WorldState::actionPreMatch(const Action *ac, const paramlist *params) const
   {
      // Check static predicates.
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

      // Check parameter predicates.
      if(params && params->size() == ac->getNumParams())
      {
         const actionparams &apl = ac->getRequiredParams();
         actionparams::const_iterator pit;

         for(pit = apl.begin(); pit != apl.end(); pit++)
         {
            if(!predicateSet(pit->first))
               return false;
            // If the predicate is set to the wrong value, fail.
            if(getPredicate(pit->first) != params->at(pit->second))
               return false;
         }
      }

      return true;
   }

   /// This method compares a desired world state with an action's results. The
   /// comparison returns true if each predicate in our current state is either
   /// set by the Action, or required by it and not changed.
   /// In this method, params is an output argument. The method fills in the
   /// values of each parameter required for the Action to result in the given
   /// world state.
   /// @todo Review complexity of this method.
   bool WorldState::actionPostMatch(const Action *ac, const paramlist *params) const
   {
      worldrep::const_iterator it;
      worldrep::const_iterator ait;
      worldrep::const_iterator rit;
      actionparams::const_iterator plit;

      const worldrep &set = ac->getSet();
      const worldrep &req = ac->getRequired();
      const actionparams &preq = ac->getRequiredParams();
      const actionparams &pset = ac->getSetParams();

      unsigned int matched = 0;

      // Check each of our predicates.
      for(it = mState.begin(); it != mState.end(); it++)
      {
         // Does this Action set this predicate to some value?
         ait = set.find(getPName(it));
         if(ait != set.end())
         {
            // Action touches this predicate; check value is correct.
            if(getPVal(ait) == getPredicate(getPName(ait)))
            {
               matched++;
               continue;
            }
            else
               return false;
         }
         else
         {
            // Action does not set this predicate to a constant. Check params.
            plit = pset.find(getPName(it));
            if(plit != pset.end())
            {
               // Check if value matches.
               if(params && params->size() == ac->getNumParams() &&
                  params->at(plit->second) == getPredicate(plit->first))
               {
                  matched++;
                  continue;
               }
               else
                  return false;
            }
            else
            {
               // Predicate is not set anywhere. Is it required?
               rit = req.find(getPName(it));
               if(rit != req.end())
               {
                  // Check to see if is is required to be the right value.
                  if(rit->second == getPredicate(rit->first))
                  {
                     matched++;
                     continue;
                  }
                  else
                     return false;
               }
               else
               {
                  // Check to see if required to a parameter.
                  plit = preq.find(getPName(it));
                  if(plit != preq.end())
                  {
                     if(params && params->size() == ac->getNumParams() &&
                        params->at(plit->second) == getPredicate(plit->first))
                     {
                        matched++;
                        continue;
                     }
                     else
                        return false;
                  }
               }
            }
         }
      }

      return matched != 0;
   }

   /// Apply an Action to the current world state. The Action's effects are
   /// applied to the current set of predicates.
   void WorldState::applyActionForward(const Action *ac, const paramlist *params)
   {
      worldrep::const_iterator sit;
      pnamelist::const_iterator pit;

      // Predicates set by this Action.
      const worldrep &st = ac->getSet();
      for(sit = st.begin(); sit != st.end(); sit++)
         _setPredicate(getPName(sit), getPVal(sit));

      // Predicates unset.
      const pnamelist &pr = ac->getCleared();
      for(pit = pr.begin(); pit != pr.end(); pit++)
         _unsetPredicate(*pit);

      // Predicate set to a parameter.
      if(params && params->size() == ac->getNumParams())
      {
         const actionparams &pl = ac->getSetParams();
         actionparams::const_iterator plit;
         for(plit = pl.begin(); plit != pl.end(); plit++)
            _setPredicate(plit->first, params->at(plit->second));
      }

      updateHash();
   }

   /// This method applies an Action to a WorldState in reverse. In effect,
   /// it determines the state of the world required that when this Action is
   /// applied to it, the result is the current state.
   /// This involves making sure that the new state's predicates match the
   /// Action's prerequisites, and clearing any predicates that the Action
   /// sets.
   void WorldState::applyActionReverse(const Action *ac, const paramlist *params)
   {
      worldrep::const_iterator sit;
      pnamelist::const_iterator pit;
      actionparams::const_iterator plit;

      // Predicates that are touched by the Action are unset.
      const worldrep &set = ac->getSet();
      for(sit = set.begin(); sit != set.end(); sit++)
         _unsetPredicate(getPName(sit));
      const pnamelist &pr = ac->getCleared();
      for(pit = pr.begin(); pit != pr.end(); pit++)
         _unsetPredicate(*pit);
      if(params && params->size() == ac->getNumParams())
      {
         const actionparams &pl = ac->getSetParams();
         for(plit = pl.begin(); plit != pl.end(); plit++)
            _unsetPredicate(plit->first);
      }

      // Predicates that must be some value. This may re-set some of the
      // predicates that were unset above.
      const worldrep &req = ac->getRequired();
      for(sit = req.begin(); sit != req.end(); sit++)
         _setPredicate(getPName(sit), getPVal(sit));
      if(params && params->size() == ac->getNumParams())
      {
         const actionparams &pl = ac->getRequiredParams();
         for(plit = pl.begin(); plit != pl.end(); plit++)
            _setPredicate(plit->first, params->at(plit->second));
      }

      updateHash();
   }

   /// This hash method sums the string hashes of all the predicate names in
   /// this state, XORing certain bits based on the values of each predicate.
   /// @todo Is there a better hash func to use? Should do some unit testing.
   void WorldState::updateHash()
   {
      mHash = 0;
      worldrep::const_iterator it;
      for(it = mState.begin(); it != mState.end(); it++)
      {
         //unsigned int l = getPName(it).length();
         //while(l)
         //   mHash = 31 * mHash + getPName(it)[--l];
         //mHash ^= getPVal(it) << getPName(it).length() % (sizeof(unsigned int) - sizeof(PVal));
         mHash = 31 * mHash + (getPName(it) << getPVal(it));
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
         int cmp = getPName(p1) != getPName(p2);
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
