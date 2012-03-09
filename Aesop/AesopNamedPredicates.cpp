/// @file AesopNamedPredicates.cpp
/// Implementation of NamedPredicates class as defined in AesopNamedPredicates.h

#include "AesopNamedPredicates.h"

namespace Aesop {
   /// @class NamedPredicates
   ///
   /// This class works similarly to SimplePredicates in that its predicates
   /// are simple flags and indexed by their ID numbers. However, this class
   /// allows each ID number to be associated with a name.

   /// When a predicate name is defined, NamedPredicates stores it as the value
   /// in a map where the key is the predicate ID, a number which is auto-
   /// incremented as you add predicates.
   NamedPredicates &NamedPredicates::define(name n)
   {
      mPredicates[n] = mPredicates.size();
      return *this;
   }

   /// This method takes logarithmic time in the number of predicates defined.
   Predicates::predID NamedPredicates::find(name n) const
   {
      predicatemap::const_iterator it = mPredicates.begin();
      if(it != mPredicates.end())
         return it->second;
      return NullPredicate;
   }

   unsigned int NamedPredicates::size() const
   {
      return mPredicates.size();
   }

   /// This method takes constant time.
   bool NamedPredicates::has(predID pred) const
   {
      return pred < size();
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
