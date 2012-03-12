/// @file AesopObjectMap.h
/// Definition of ObjectMap class.

#ifndef _AE_OBJECTMAP_H_
#define _AE_OBJECTMAP_H_

#include "abstract/AesopObjects.h"
#include <map>

namespace Aesop {
   /// A set of objects of user-specified type.
   /// @ingroup Aesop
   template < class O >
   class ObjectMap : public Objects {
   public:
      /// @name Object management
      /// @{

      /// Create a new object.
      /// @param[in] object New object value to add.
      /// @param[in] type   Type the object should be of.
      /// @param[in] id     The ID number that this object must be associated
      ///                   with. May overwrite an existing object definition.
      /// @return ID of the new object.
      objectID create(const O &object, Types::typeID type = Types::NullType, objectID id = NullObject);

      /// Return the object associated with a particular ID.
      /// @param[in] id ID number to look for.
      /// @return Pointer to the object if it exists, or NULL if not.
      O *get(objectID id);

      /// Remove the object with a particular ID number.
      /// @param[in] id ID of the object to remove.
      void erase(objectID id);

      /// @}

      /// @name Objects
      /// @{

      virtual bool has(objectID obj) const;
      virtual Types::typeID typeof(objectID obj) const;

      virtual unsigned int size() const { return mObjects.size(); }
      virtual const_iterator begin() const { return 0; }
      virtual const_iterator end() const { return 0; }

      /// @}

      /// Default constructor.
      /// @param[in] types Types set to validate objects.
      ObjectMap(const Types &types = NoTypes) : Objects(types), mCurID(0) {}

   private:
      /// Map from object ID numbers to the user-defined type.
      typedef std::map<objectID, std::pair<O, Types::typeID> > objectmap;
      objectmap mObjects;
      unsigned int mCurID;
   };

   /// @class ObjectMap
   ///
   /// The ObjectMap class acts as a template for storing user-defined object
   /// data in a format that can be passed through Aesop and used in planning
   /// routines.

   template < class O >
   Objects::objectID ObjectMap<O>::create(const O &object, Types::typeID type, objectID id)
   {
      if(id == NullObject)
         id = mCurID++;
      mObjects[id] = std::make_pair(object, type);
      return id;
   }

   template < class O >
   O *ObjectMap<O>::get(objectID id)
   {
      objectmap::iterator it = mObjects.find(id);
      if(it != mObjects.end())
         return &(it->second.first);
      return NULL;
   }
   
   template < class O >
   void ObjectMap<O>::erase(objectID id)
   {
   }

   template < class O >
   bool ObjectMap<O>::has(objectID obj) const
   {
      return mObjects.find(obj) != mObjects.end();
   }
   
   template < class O >
   Types::typeID ObjectMap<O>::typeof(objectID obj) const
   {
      objectmap::const_iterator it = mObjects.find(obj);
      if(it != mObjects.end())
         return it->second.second;
      return Types::NullType;
   }
};

#endif
