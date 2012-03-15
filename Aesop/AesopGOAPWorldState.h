/// @file AesopGOAPWorldState.h
/// Definition of GOAPWorldState class.

#ifndef _AE_GOAPWORLDSTATE_H_
#define _AE_GOAPWORLDSTATE_H_

#include <vector>
#include <map>
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
      virtual std::string repr() const;

      /// @}

      void set(Predicates::predID pred, Objects::objectID param) { _set(pred, param); updateHash(); }

      /// @name Comparisons
      /// @{

      unsigned int compare(const GOAPWorldState &other) const;

      virtual bool operator==(const GOAPWorldState &other) const
      {
         return mHash != other.mHash ? false : compare(other) == 0;
      }

      virtual bool operator!=(const GOAPWorldState &other) const
      {
         return mHash != other.mHash ? true : compare(other) != 0;
      }

      /// @}

      /// Default constructor.
      GOAPWorldState(const Predicates &p);
      /// Default destructor.
      ~GOAPWorldState();

   protected:
   private:
      /// Set a predicate without updating our hash.
      /// @see WorldState::set
      void _set(Predicates::predID pred, Objects::objectID param);
      /// Unset a predicate without updating our hash.
      /// @see WorldState::unset
      void _unset(Predicates::predID pred, Objects::objectID param);

      /// Hashed representation of this state, used for quick comparison.
      int mHash;
      /// Update our hash value.
      void updateHash();

      /// World representation.
      typedef std::map<Predicates::predID, Objects::objectID> worldrep;
      /// Store world state.
      worldrep mWorld;
   };
};

#endif
