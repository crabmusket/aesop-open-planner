/// @file AesopSimplePredicates.h
/// Definition and implementation of SimplePredicates class.

#ifndef _AE_SIMPLE_PREDICATES_H_
#define _AE_SIMPLE_PREDICATES_H_

#include "abstract/AesopPredicates.h"

namespace Aesop {
   /// Simplest Predicates implementation.
   ///
   /// This Predicates implementation allows the user to define a certain
   /// number of predicates, whose ID numbers will simply run from 0 to one
   /// less than the number defined. This makes SimplePredicates ideal to use
   /// when predicates are defined in an enum{}. Predicates act as simple
   /// boolean flags - they may not have parameters.
   ///
   /// @ingroup Aesop
   class SimplePredicates : public Predicates {
   public:
      /// Define this many predicates.
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

      /// Default constructor. Zero predicates are defined.
      SimplePredicates() : mNumPredicates(0) {}
   protected:
   private:
      /// Number of predicates defined.
      unsigned int mNumPredicates;
   };
};

#endif
