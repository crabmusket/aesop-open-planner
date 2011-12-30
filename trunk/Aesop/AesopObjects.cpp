/// @file AesopObjects.cpp
/// @brief Implementation of Objectss class as defined in AesopObjects.h

#include "AesopObjects.h"

namespace ae {
   /// @class Objects
   ///
   /// A set of named objects that exist in a particular problem. The container
   /// is designed to offer fast iteration through all objects defined. It also
   /// defines a 'type_iterator' for convenience, which will only produce
   /// the names of objects of a specified type. However, iterating through a
   /// container this way is still linear in the size of the container as a
   /// whole, performance-wise.

   Objects::Objects(const Types &types)
      : mTypes(types)
   {
   }

   Objects::~Objects()
   {
   }

   void Objects::add(std::string name, std::string type)
   {
      // Check type.
      if(!mTypes.has(type))
         return;
      // Insert new object.
      mObjects[name] = type;
   }

   void Objects::remove(std::string name)
   {
      mObjects.erase(name);
   }

   bool Objects::has(std::string name) const
   {
      return mObjects.find(name) != mObjects.end();
   }

   std::string Objects::typeof(std::string name) const
   {
      objectmap::const_iterator it = mObjects.find(name);
      if(it != mObjects.end())
         return it->second;
      return "";
   }

   unsigned int Objects::size(std::string type) const
   {
      if(type.empty())
         return mObjects.size();
      unsigned int count = 0;
      for(type_iterator it = begin(type); it != end(type); it++)
         count++;
      return count;
   }
};
