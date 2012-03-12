/// @file AesopObjects.h
/// Definition of Objects class.

#ifndef _AE_OBJECTS_H_
#define _AE_OBJECTS_H_

#include "AesopTypes.h"

namespace Aesop {
   /// A set of objects defined in a particular planning problem.
   /// @ingroup Aesop
   class Objects {
   public:
      /// Objects must be identifiable.
      typedef unsigned int objectID;
      /// Null object identifier.
      static const objectID NullObject;

      /// Do we have an object of the given identifier?
      /// @param obj Look for an object with this identifier.
      /// @return True if we have an object with that identifier, false if not.
      virtual bool has(objectID obj) const = 0;

      /// Get the type of an object.
      /// @param obj Identifier of the object to get the type of.
      /// @return The object's type.
      virtual Types::typeID typeof(objectID obj) const = 0;

      /// Get our types object.
      /// @return Handle of our types.
      const Types &getTypes() const { return mTypes; }

      /// @name Partial STL interface
      /// @{

      /// Iteration simply uses an ID.
      typedef objectID const_iterator;
      /// Return the number of objects stored.
      virtual unsigned int size() const = 0;
      /// Iterator to first object.
      virtual const_iterator begin() const = 0;
      /// Iterator to one-after-last object.
      virtual const_iterator end() const = 0;

      /// Iterator that sticks to a particular type and its descendents.
      struct type_iterator
      {
         /// Default constructor.
         /// @param[in] i Index to start at. 
         /// @param[in] o Objects this iterator operates on.
         /// @param[in] t Type to restrict our iteration to.
         type_iterator(const_iterator i, const Objects &o, const Types::typeID &t)
            : it(i), objs(o), type(t)
         {
            if(it != objs.end() && !objs.getTypes().isOf(it, type))
               ++(*this);
         }

         /// @name Iteration
         /// @{

         type_iterator &operator++()
         {
            it++;
            while(it != objs.end() && !objs.getTypes().isOf(it, type))
               it++;
            return *this;
         }

         type_iterator operator++(int)
         {
            type_iterator result(*this);
            ++(*this);
            return result;
         }

         /// @}

         /// @name Interface
         /// @{

         bool operator==(const type_iterator &other) const
         { return it == other.it; }
         bool operator!=(const type_iterator &other) const
         { return it != other.it; }

         /// @}

      private:
         /// Reference to the Objects we iterate over.
         const Objects &objs;
         /// Internal iterator.
         const_iterator it;
         /// Type name to restrict ourselves to.
         Types::typeID type;
      };

      /// Iterator to the first object of a particular type.
      type_iterator begin(Types::typeID type) const { return type_iterator(begin(), *this, type); }
      /// Iterator to the one-after-last object.
      type_iterator end(Types::typeID type) const { return type_iterator(end(), *this, type); }

      /// @}

      /// Default constructor.
      /// @param[in] types Types set to validate objects.
      Objects(const Types &types = NoTypes) : mTypes(types) {}

   protected:
      /// Alternate name for has method.
      /// @see Objects::has
      bool have(Types::typeID name) const { return has(name); }

   private:
      /// Types that validate our objects.
      const Types &mTypes;
   };

   /// No objects.
   /// @ingroup Aesop
   class NullObjects : public Objects {
   public:
      bool has(objectID obj) const { return false; }
      Types::typeID typeof(objectID obj) const { return Types::NullType; }
      unsigned int size() const { return 0; }
      const_iterator begin() const { return 0; }
      const_iterator end() const { return 0; }
   protected:
   private:
   };

   /// No objects.
   const NullObjects NoObjects;
};

#endif
