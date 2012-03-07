/// @file AesopSimplePredicates.h
/// Definition and implementation of SimplePredicates class.

#ifndef _AE_SIMPLE_PREDICATES_H_
#define _AE_SIMPLE_PREDICATES_H_

#include "AesopPredicates.h"

namespace Aesop {
   /// Simplest Predicates implementation.
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

      /// Default constructor.
      SimplePredicates() : mNumPredicates(0) {}
   protected:
   private:
      /// Number of predicates defined.
      unsigned int mNumPredicates;
   };
};

#endif
