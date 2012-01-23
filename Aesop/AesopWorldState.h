/// @file AesopWorldState.h
/// @brief Definition of WorldState class.

#ifndef _AE_WORLDSTATE_H_
#define _AE_WORLDSTATE_H_

#include "AesopPredicates.h"
#include "AesopActionSet.h"

namespace ae {
   /// @brief Knowledge about a state of the world, current or possible.
   /// @ingroup Aesop
   template<typename n, typename v>
   class WorldStateTemplate {
   public:
      typedef n pname;
      typedef v pval;

      /// @brief Is the predicate set to a value?
      /// @param[in] pred Name of the predicate to check.
      /// @return True iff the predicate is set to some valid value.
      virtual bool isSet(pname pred) const = 0;

      /// @brief Get the value of a predicate.
      /// @param[in] pred Name of predicate to check.
      /// @param[in] def  Default predicate value if unset.
      /// @return The value of the predicate
      virtual pval get(pname pred, pval def) const = 0;

      /// @brief Set the value of a predicate.
      /// @param[in] pred Name of predicate to set.
      /// @param[in] val Value to set the predicate to.
      virtual void set(pname pred, pval val) = 0;

      /// @brief Remove our knowledge of a certain predicate.
      /// @param[in] pred Name of the predicate to clear.
      virtual void unset(pname pred) = 0;

      /// @brief Do the given Action's pre-conditions match this world state?
      /// @param[in] ac     Action instance to test against this world state.
      /// @param[in] params Parameters to the Action instance if it takes any.
      /// @return True iff the Action is valid under the current world state.
      //virtual bool actionPreMatch(const Action &ac, const paramlist *params = NULL) const = 0;

      /// @brief Does the given Action, executed from an arbitrary world state,
      ///        result in this world state?
      /// @param[in]  ac     Action to compare.
      /// @param[out] params Parameters the Action must use for it to result in
      ///                    this world state.
      /// @return True iff the Action results in the current world state.
      //virtual bool actionPostMatch(const Action &ac, const paramlist *params = NULL) const = 0;

      /// @brief Apply the given Action to this WorldState in the forwards
      ///        direction.
      /// @param[in] ac     Action to apply to the current state of the world.
      /// @param[in] params Parameters to the Action instance if it takes any.
      //virtual void applyActionForward(const Action &ac, const paramlist *params = NULL) = 0;

      /// @brief Remove the effects of the given Action from the world.
      /// @param[in] ac     Action to remove from the current state.
      /// @param[in] params Parameters to the Action instance if it takes any.
      //virtual void applyActionReverse(const Action &ac, const paramlist *params = NULL) = 0;

      /// @brief Compare two world states.
      /// @param[in] ws1 First WorldState to compare.
      /// @param[in] ws2 Another WorldState to compare.
      /// @return Number of predicates that differ in value between states.
      //static unsigned int comp(const WorldState<n, v> &ws1, const WorldState<n, v> &ws2) = 0;

      /// @brief Boolean equality test.
      /// This equality test will compare WorldStates based on their hash codes,
      /// providing a faster negative result. If their hash codes are equal, then
      /// WorldState::comp is used to verify.
      //virtual bool operator==(const WorldStateTemplate<n, v> &s) const = 0;

      /// @brief Boolean inequality test.
      //virtual bool operator!=(const WorldStateTemplate<n, v> &s) const = 0;

      /// @brief Get the PredicatesTemplate object used by this WorldStateTemplate.
      /// @return A PredicatesTemplate object of the same type.
      const PredicatesTemplate<pname> &getPredicates() { return mPredicates; }

      WorldStateTemplate(const PredicatesTemplate<n> &p) : mPredicates(p) {}

   protected:
   private:
      const PredicatesTemplate<n> &mPredicates;
   };

   /// @brief Default fully-featured world state.
   /// @ingroup Aesop
   class WorldState : public WorldStateTemplate<std::string, bool> {
   public:
      virtual bool isSet(pname pred) const;
      virtual pval get(pname pred, pval def = false) const;
      virtual void set(pname pred, pval val);
      virtual void unset(pname pred);

      /// @TODO Reinstate some form of comparison between WorldStateTemplate subclasses.
      virtual bool operator==(const WorldState &s) const
      { return mHash != s.mHash ? false : true; }
      virtual bool operator!=(const WorldState &s) const
      { return !operator==(s); }

      /// @brief Default constructor.
      WorldState(const PredicatesTemplate<pname> &p);
      /// @brief Default destructor.
      ~WorldState();
   protected:
   private:
      typedef std::map<pname, pval> worldrep;
      /// @brief Stores representation of world state.
      worldrep mState;
      /// @brief Computed hash value of this WorldState.
      int mHash;

      /// @brief Set a predicate value without updating our hash.
      void _set(pname pred, pval val);
      /// @brief Unset a predicate value without updating our hash.
      void _unset(pname pred);

      /// @brief Update our hash value.
      void updateHash();

      /// @brief Get the name of the world state entry.
      inline pname getPName(worldrep::const_iterator it) const
      { return it->first; }
      /// @brief Get the Predicate of the world state entry.
      inline pval getPVal(worldrep::const_iterator it) const
      { return it->second; }
   };

   /// @brief Performant but limited world state storage.
   /// @ingroup Aesop
   class GOAPWorldState : public WorldStateTemplate<unsigned int, int> {
   public:
      virtual bool isSet(pname pred) const;
      virtual pval get(pname pred, pval def = false) const;
      virtual void set(pname pred, pval val);
      virtual void unset(pname pred);

      virtual bool operator==(const GOAPWorldState &s) const
      { return mHash != s.mHash ? false : true; }
      virtual bool operator!=(const GOAPWorldState &s) const
      { return !operator==(s); }

      /// @brief Default constructor.
      GOAPWorldState(const PredicatesTemplate<pname> &p);
      /// @brief Default destructor.
      ~GOAPWorldState();
   protected:
   private:
      /// @brief Store a fact about the world.
      struct fact {
         bool set;
         pval value;
         fact() : set(false), value() {}
      };
      typedef std::vector<fact> worldrep;
      /// @brief Stores representation of world state.
      worldrep mState;
      /// @brief Computed hash value of this WorldState.
      int mHash;

      /// @brief Set a predicate value without updating our hash.
      void _set(pname pred, pval val);
      /// @brief Unset a predicate value without updating our hash.
      void _unset(pname pred);

      /// @brief Update our hash value.
      void updateHash();
   };
};

#endif
