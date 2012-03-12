/// @file AesopGOAPWorldState.h
/// Definition of GOAPWorldState class.

#ifndef _AE_GOAPWORLDSTATE_H_
#define _AE_GOAPWORLDSTATE_H_

#include <vector>
#include "abstract/AesopWorldState.h"

namespace Aesop {
   /// Single-parameter WorldState implementation.
   /// @ingroup Aesop
   class GOAPWorldState : public WorldState {
   public:
      /// @name WorldState
      /// @{

      virtual bool isSet(Predicates::predID pred, const paramlist &params = paramlist()) const;
      virtual bool isUnset(Predicates::predID pred, const paramlist &params = paramlist()) const
      { return !isSet(pred, params); }
      virtual void set(Predicates::predID pred, const paramlist &params = paramlist());
      virtual void unset(Predicates::predID pred, const paramlist &params = paramlist());
      virtual WorldState *clone() const;
      virtual std::string repr() const;

      unsigned int compare(const WorldState &other) const;

      virtual bool operator==(const WorldState &other) const
      {
         const GOAPWorldState *ws = dynamic_cast<const GOAPWorldState*>(&other);
         return ws != 0 && mHash != ws->mHash ? false : compare(*ws) == 0;
      }
      virtual bool operator!=(const WorldState &other) const
      {
         const GOAPWorldState *ws = dynamic_cast<const GOAPWorldState*>(&other);
         return ws == 0 || mHash != ws->mHash ? true : compare(*ws) != 0;
      }

      /// @}

      GOAPWorldState(const Predicates &p);
      ~GOAPWorldState();

   protected:
   private:
      /// Set a predicate without updating our hash.
      /// @see WorldState::set
      void _set(Predicates::predID pred, const paramlist &params);
      /// Unset a predicate without updating our hash.
      /// @see WorldState::unset
      void _unset(Predicates::predID pred, const paramlist &params);

      /// Hashed representation of this state, used for quick comparison.
      int mHash;
      /// Update our hash value.
      void updateHash();

   };
};

#endif
