/// @file AesopGOAPWorldState.cpp
/// Implementation of GOAPWorldState class as defined in AesopGOAPWorldState.h

#include "AesopGOAPWorldState.h"

namespace Aesop {
   /// @class GOAPWorldState
   ///
   /// This WorldState allows a single parameter pre predicate.

   GOAPWorldState::GOAPWorldState(const Predicates &p) : WorldState(p)
   {
      mHash = 0;
   }

   GOAPWorldState::~GOAPWorldState()
   {
   }

   bool GOAPWorldState::isSet(Predicates::predID pred, const paramlist &params) const
   {
      return false;
   }

   void GOAPWorldState::set(Predicates::predID pred, const paramlist &params)
   {
      if(false)
      {
         _set(pred, params);
         updateHash();
      }
   }

   void GOAPWorldState::_set(Predicates::predID pred, const paramlist &params)
   {
   }

   void GOAPWorldState::unset(Predicates::predID pred, const paramlist &params)
   {
      if(false)
      {
         _unset(pred, params);
         updateHash();
      }
   }

   void GOAPWorldState::_unset(Predicates::predID pred, const paramlist &params)
   {
   }

   WorldState *GOAPWorldState::clone() const
   {
      return new GOAPWorldState(*this);
   }

   std::string GOAPWorldState::repr() const
   {
      std::string str = "{";
      str += "}";
      return str;
   }

   unsigned int GOAPWorldState::compare(const GOAPWorldState &other) const
   {
      unsigned int diff = 0;
      return diff;
   }

   void GOAPWorldState::updateHash()
   {
   }
};
