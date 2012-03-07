/// @file AesopNamedPredicates.cpp
/// Implementation of NamedPredicates class as defined in AesopNamedPredicates.h

#include "AesopNamedPredicates.h"

namespace Aesop {
   /// When a predicate name is defined, NamedPredicates stores it as the value
   /// in a map where the key is the predicate ID, a number which is auto-
   /// incremented as you add predicates.
   NamedPredicates &NamedPredicates::define(name n)
   {
      mPredicates[mPredicates.size()] = n;
      return *this;
   }

   /// This method takes linear time in the number of predicates defined, since
   /// the storage map is keyed to a predicate's ID, not its name.
   Predicates::predID NamedPredicates::find(name n) const
   {
      predicatemap::const_iterator it = mPredicates.begin();
      for(; it != mPredicates.end(); it++)
         if(it->second == n)
            return it->first;
      return NullPredicate;
   }

   unsigned int NamedPredicates::size() const
   {
      return mPredicates.size();
   }

   /// This method takes logarithmic time in the number of predicates defined.
   /// A possible improvement would be to use an unordered_map.
   bool NamedPredicates::has(predID pred) const
   {
      return mPredicates.find(pred) != mPredicates.end();
   }

   bool NamedPredicates::operator==(const Predicates &other) const
   {
      const NamedPredicates *np = dynamic_cast<const NamedPredicates*>(&other);
      // Make sure the object is of type NamedPredicates.
      if(np == 0)
         return false;
      // Sizes must be equal.
      if(np->size() != size())
         return false;
      predicatemap::const_iterator it = mPredicates.begin(), oit = np->mPredicates.begin();
      for(; it != mPredicates.end() && oit != np->mPredicates.end(); it++, oit++)
      {
         // If any predicates are different, we're done.
         if(it != oit)
            return false;
      }
      return true;
   }

   bool NamedPredicates::operator!=(const Predicates &other) const
   {
      return !operator==(other);
   }
};
