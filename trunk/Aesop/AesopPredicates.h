/// @file AesopPredicates.h
/// @brief Definition of Predicates class.

#ifndef _AE_PREDICATES_H_
#define _AE_PREDICATES_H_

#include "AesopTypes.h"

namespace Aesop {
   /// @brief A set of Predicates defined in a particular planning problem.
   /// @ingroup Aesop
   class Predicates {
   public:
      /// @brief Type that identifies a predicate.
      typedef unsigned int predID;

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
      /// @}

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

      /// @brief Default constructor.
      SimplePredicates() : mNumPredicates(0) {}
   protected:
   private:
      /// @brief Number of predicates defined.
      unsigned int mNumPredicates;
   };
};

#endif
