/// @file AesopTypes.h
/// @brief Definition of Types class.

#ifndef _AE_TYPES_H_
#define _AE_TYPES_H_

namespace Aesop {
   /// @brief A set of types defined for a planning problem.
   /// @ingroup Aesop
   class Types {
   public:
      /// @brief All types boil down to a simple ID.
      typedef unsigned int typeID;
      /// @brief Special constant to represent the absence of type.
      static const typeID NullType;

      /// @brief Is the type defined?
      /// @param type Type name to check.
      /// @return True if the type is defined, false if not.
      virtual bool has(typeID type) const = 0;

      /// @brief Is the former a descendent of the latter?
      /// @param type     The type to verify.
      /// @param ancestor The ancestor type to check for.
      /// @return True if 'type' is a type of 'ancestor'.
      virtual bool isOf(typeID type, typeID ancestor) const = 0;

      /// @brief Get number of types defined not including NullType.
      /// @return Number of user-defined types.
      virtual unsigned int size() const = 0;

   protected:
      /// @brief Alternate name for has method.
      /// @see Types::has
      bool have(typeID type) const { return has(type); }

   private:
   };

   /// @brief Implementation of Types that allows no types.
   /// @ingroup Aesop
   class NullTypes : public Types {
   public:
      bool has(typeID type) const { return type == NullType; }
      bool isOf(typeID type, typeID ancestor) const { return false; }
      unsigned int size() const { return 0; }
   protected:
   private:
   };

   /// @brief No types defined.
   const NullTypes NoTypes;
};

#endif
