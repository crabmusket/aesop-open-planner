/// @file AesopSimpleWorldState.cpp
/// Implementation of SimpleWorldState class as defined in AesopSimpleWorldState.h

#include "AesopSimpleWorldState.h"

namespace Aesop {
   /// @class SimpleWorldState
   ///
   /// This WorldState operates on predicates that are simple boolean flags -
   /// it ignores parameters.

   SimpleWorldState::SimpleWorldState(const Predicates &p) : WorldState(p)
   {
      mHash = 0;
      mState.resize(getPredicates().size());
   }

   SimpleWorldState::~SimpleWorldState()
   {
   }

   bool SimpleWorldState::isSet(Predicates::predID pred, const paramlist &params) const
   {
      return pred < mState.size() && mState[pred].set;
   }

   void SimpleWorldState::set(Predicates::predID pred, const paramlist &params)
   {
      if(pred < mState.size())
      {
         _set(pred, params);
         updateHash();
      }
   }

   void SimpleWorldState::_set(Predicates::predID pred, const paramlist &params)
   {
      mState[pred].set = true;
   }

   void SimpleWorldState::unset(Predicates::predID pred, const paramlist &params)
   {
      if(pred < mState.size())
      {
         _unset(pred, params);
         updateHash();
      }
   }

   void SimpleWorldState::_unset(Predicates::predID pred, const paramlist &params)
   {
      mState[pred].set = false;
   }

   WorldState *SimpleWorldState::clone() const
   {
      return new SimpleWorldState(*this);
   }

   std::string SimpleWorldState::repr() const
   {
      std::string str = "{";
      worldrep::const_iterator it = mState.begin();
      while(it != mState.end())
      {
         str += it->set ? "t" : "f";
         if(++it != mState.end())
            str += ", ";
      }
      str += "}";
      return str;
   }

   unsigned int SimpleWorldState::compare(const SimpleWorldState &other) const
   {
      unsigned int diff = 0;
      worldrep::const_iterator it;
      worldrep::const_iterator oit;
      for(it = mState.begin(), oit = other.mState.begin();
          it != mState.end() && oit != other.mState.end();
          it++, oit++)
      {
         if(it->set != oit->set)
            diff++;
      }
      return diff;
   }

   void SimpleWorldState::updateHash()
   {
      mHash = mState.size();
      worldrep::const_iterator it;
      unsigned int i;
      for(it = mState.begin(), i = 0; it != mState.end(); it++, i++)
         mHash ^= it->set ? i : 0;
   }
};
