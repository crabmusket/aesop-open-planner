/// @file AesopTypedObjects.h
/// Definition and implementation of TypedObjects class.

#ifndef _AE_TYPEDOBJECTS_H_
#define _AE_TYPEDOBJECTS_H_

#include "abstract/AesopObjects.h"
#include <map>

namespace Aesop {
   /// A set of arbitrary object IDs with types.
   /// @ingroup Aesop
   class TypedObjects : public Objects {
   public:
      /// @name Object management
      /// @{

      /// Create a new object.
      /// @param[in] id   The ID number for this object.
      /// @param[in] type The type of this object.
      void create(objectID id, Types::typeID type = Types::NullType) { mObjects[id] = type; }

      /// Remove the object with a particular ID number.
      /// @param[in] id ID of the object to remove.
      void erase(objectID id) { mObjects.erase(id); }

      /// @}

      /// @name Objects
      /// @{

      virtual bool has(objectID obj) const { return mObjects.find(obj) != mObjects.end(); }
      virtual Types::typeID typeof(objectID obj) const
      {
         objectmap::const_iterator it = mObjects.find(obj);
         if(it != mObjects.end())
            return it->second;
         return Types::NullType;
      };

      virtual unsigned int size() const { return mObjects.size(); }
      virtual const_iterator begin() const { return 0; }
      virtual const_iterator end() const { return 0; }

      /// @}

      /// Default constructor.
      /// @param[in] types Types set to validate objects.
      TypedObjects(const Types &types) : Objects(types) {}

   private:
      /// Map from object ID numbers to the user-defined type.
      typedef std::map<objectID, Types::typeID> objectmap;
      objectmap mObjects;
   };
};

#endif
