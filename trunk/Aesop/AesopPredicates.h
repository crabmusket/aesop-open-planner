/// @file AesopPredicates.h
/// @brief Definition of Predicates class.

#ifndef _AE_PREDICATES_H_
#define _AE_PREDICATES_H_

#include <string>
#include <map>
#include "AesopTypes.h"

namespace Aesop {
   /// @brief A set of Predicates defined in a particular planning problem.
   /// @ingroup Aesop
   class Predicates {
   public:
      /// @brief Type that identifies a predicate.
      typedef unsigned int predID;
      /// @brief Constant for null predicate.
      static const predID NullPredicate;

      /// @brief Number of predicates we define.
      /// @return Number of predicates defined.
      virtual unsigned int size() const = 0;

      /// @brief Do we have this predicate?
      /// @param[in] pred Look for predicates with this identifier.
      /// @return True iff we have a predicate with that identifier.
      virtual bool has(predID pred) const = 0;

      /// @brief Boolean comparison fails unless subclasses override this
      ///        operator.
      virtual bool operator==(const Predicates &other) const { return false; }
      virtual bool operator!=(const Predicates &other) const { return true; }

   protected:
      /// @brief Alternate name for has method.
      /// @see Predicates::has
      bool have(predID pred) const { return has(pred); }

   private:
   };

   /// @brief Simplest Predicates implementation.
   /// @ingroup Aesop
   class SimplePredicates : public Predicates {
   public:
      /// @brief Define this many predicates.
      void define(unsigned int num) { mNumPredicates = num; }

      /// @name Predicates
      /// @{

      virtual unsigned int size() const { return mNumPredicates; }
      virtual bool has(predID pred) const { return pred < size(); }
      bool operator==(const Predicates &other) const
      {
         const SimplePredicates *sp = dynamic_cast<const SimplePredicates*>(&other);
         return sp != 0 && sp->size() == size();
      }
      bool operator!=(const Predicates &other) const
      {
         const SimplePredicates *sp = dynamic_cast<const SimplePredicates*>(&other);
         return sp == 0 || sp->size() != size();
      }

      /// @}

      /// @brief Default constructor.
      SimplePredicates() : mNumPredicates(0) {}
   protected:
   private:
      /// @brief Number of predicates defined.
      unsigned int mNumPredicates;
   };

   /// @brief Predicates identified by name.
   class NamedPredicates : public Predicates {
   public:
      /// @brief Predicate names are stored as strings.
      typedef std::string name;

      /// @brief Define a predicate with this name:
      /// @param[in] n Name of the new predicate.
      /// @return This object.
      NamedPredicates &define(name n);

      /// @brief Find a predicate with the given name.
      /// @param[in] n Name of the predicate to look for.
      /// @return The ID of the predicate if found, or else NullPredicate.
      predID find(name n);

      /// @name Predicates
      /// @{

      virtual unsigned int size() const;
      virtual bool has(predID pred) const;
      virtual bool operator==(const Predicates &other) const;
      virtual bool operator!=(const Predicates &other) const;

      /// @}

   protected:
      /// @brief Map predicate names to predicate ID numbers.
      typedef std::map<std::string, predID> predicatemap;

      /// @brief Store predicates.
      predicatemap mPredicates;
   private:
   };
};

#endif
