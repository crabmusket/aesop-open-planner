/// @file AesopNamedPredicates.h
/// Definition of NamedPredicates class.

#ifndef _AE_NAMED_PREDICATES_H_
#define _AE_NAMED_PREDICATES_H_

#include <string>
#include <map>
#include "AesopPredicates.h"

namespace Aesop {
   /// Predicates identified by name.
   class NamedPredicates : public Predicates {
   public:
      /// Predicate names are stored as strings.
      typedef std::string name;

      /// Define a predicate with this name:
      /// @param[in] n Name of the new predicate.
      /// @return This object.
      NamedPredicates &define(name n);

      /// Find a predicate with the given name.
      /// @param[in] n Name of the predicate to look for.
      /// @return The ID of the predicate if found, or else NullPredicate.
      predID find(name n) const;

      /// @name Predicates
      /// @{

      virtual unsigned int size() const;
      virtual bool has(predID pred) const;
      virtual bool operator==(const Predicates &other) const;
      virtual bool operator!=(const Predicates &other) const;

      /// @}

   protected:
      /// Map predicate names to predicate ID numbers.
      typedef std::map<predID, std::string> predicatemap;

      /// Store predicates.
      predicatemap mPredicates;
   private:
   };
};

#endif
