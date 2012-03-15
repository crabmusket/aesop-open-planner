/// @file AesopGOAPWorldState.cpp
/// Implementation of GOAPWorldState class as defined in AesopGOAPWorldState.h

#include "AesopGOAPWorldState.h"

// From http://www.programmersheaven.com/mb/CandCPP/79561/79561/bitwise-rotation/
static unsigned int ror32(unsigned int data, unsigned int bits) {
  return (data >> bits) | (data << (32-bits));
}
static unsigned int rol32(unsigned int data, unsigned int bits) {
  return (data << bits) | (data >> (32-bits));
}

namespace Aesop {
   /// @class GOAPWorldState
   ///
   /// This WorldState allows a single parameter per predicate.

   GOAPWorldState::GOAPWorldState(const Predicates &p) : WorldState(p)
   {
      mHash = 0;
   }

   GOAPWorldState::~GOAPWorldState()
   {
   }

   bool GOAPWorldState::isSet(Predicates::predID pred, const paramlist &params) const
   {
      if(!params.size())
         return false;
      worldrep::const_iterator it = mWorld.find(pred);
      return it != mWorld.end() && it->second == params[0];
   }

   void GOAPWorldState::set(Predicates::predID pred, const paramlist &params)
   {
      if(params.size())
      {
         _set(pred, params[0]);
         updateHash();
      }
   }

   void GOAPWorldState::_set(Predicates::predID pred, Objects::objectID param)
   {
      mWorld[pred] = param;
   }

   void GOAPWorldState::unset(Predicates::predID pred, const paramlist &params)
   {
      if(params.size())
      {
         _unset(pred, params[0]);
         updateHash();
      }
   }

   void GOAPWorldState::_unset(Predicates::predID pred, Objects::objectID param)
   {
      mWorld.erase(pred);
   }

   std::string GOAPWorldState::repr() const
   {
      std::string str = "{";
      str += "}";
      return str;
   }

   unsigned int GOAPWorldState::compare(const GOAPWorldState &other) const
   {
      return mWorld == other.mWorld ? 0 : 1;
   }

   void GOAPWorldState::updateHash()
   {
   }
};
