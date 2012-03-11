/// @file AesopSimpleTypes.h
/// Definition of SimpleTypes class.

#ifndef _AE_SIMPLETYPES_H_
#define _AE_SIMPLETYPES_H_

#include "abstract/AesopTypes.h"

namespace Aesop {
   /// Simplest types object that defines a number of types with no hierarchy.
   /// @ingroup Aesop
   class SimpleTypes : public Types {
   public:
      /// @name Type definition
      /// @{

      /// Define the given number of types.
      /// @param[in] num Number of types that should be defined.
      void define(unsigned int num) { mNumTypes = num; }

      /// @}

      /// @name Types
      /// @{

      virtual bool has(typeID type) const { return type < mNumTypes || type == NullType; }
      virtual bool isOf(typeID type, typeID ancestor) const { return ancestor == NullType; }
      virtual unsigned int size() const { return mNumTypes; }

      /// @}

   private:
      /// Number of types defined.
      unsigned int mNumTypes;
   };
};

#endif
