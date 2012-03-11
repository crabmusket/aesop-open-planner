/// @file AesopTypes.h
/// Definition of Types class.

#ifndef _AE_TYPES_H_
#define _AE_TYPES_H_

namespace Aesop {
   /// A set of types defined for a planning problem.
   /// @ingroup Aesop
   class Types {
   public:
      /// All types boil down to a simple ID.
      typedef unsigned int typeID;
      /// Special constant to represent the absence of type.
      static const typeID NullType;

      /// Is the type defined?
      /// Must always return trye if 'type' is NullType.
      /// @param type Type name to check.
      /// @return True if the type is defined or NullType, false if not.
      virtual bool has(typeID type) const = 0;

      /// Is the former a descendent of the latter?
      /// Must always return true if 'ancestor' is NullType.
      /// @param type     The type to verify.
      /// @param ancestor The ancestor type to check for.
      /// @return True if 'type' is a type of 'ancestor' or 'ancestor' is NullType.
      virtual bool isOf(typeID type, typeID ancestor) const = 0;

      /// Get number of types defined not including NullType.
      /// @return Number of user-defined types.
      virtual unsigned int size() const = 0;

   protected:
      /// Alternate name for has method.
      /// @see Types::has
      bool have(typeID type) const { return has(type); }

   private:
   };

   /// Implementation of Types that allows no types.
   /// @ingroup Aesop
   class NullTypes : public Types {
   public:
      bool has(typeID type) const { return type == NullType; }
      bool isOf(typeID type, typeID ancestor) const { return ancestor == NullType; }
      unsigned int size() const { return 0; }
   protected:
   private:
   };

   /// No types defined.
   const NullTypes NoTypes;
};

#endif
