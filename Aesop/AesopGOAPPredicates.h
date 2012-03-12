/// @file AesopGOAPPredicates.h
/// Definition of GOAPPredicates class.

#ifndef _AE_GOAPPREDICATES_H_
#define _AE_GOAPPREDICATES_H_

#include "abstract/AesopPredicates.h"

namespace Aesop {
   /// One-parameter Predicates implementation.
   /// @ingroup Aesop
   class GOAPPredicates : public Predicates {
   public:
      /// @name Predicates
      /// @{

      virtual unsigned int size() const { return 0; }
      virtual bool has(predID pred) const { return false; }
      bool operator==(const Predicates &other) const
      {
         const GOAPPredicates *gp = dynamic_cast<const GOAPPredicates*>(&other);
         return false;
      }
      bool operator!=(const Predicates &other) const
      {
         const GOAPPredicates *gp = dynamic_cast<const GOAPPredicates*>(&other);
         return false;
      }

      /// @}

      /// Default constructor.
      GOAPPredicates() {}
   protected:
   private:
   };
};

#endif
