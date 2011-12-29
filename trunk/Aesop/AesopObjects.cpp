/// @file AesopObjects.cpp
/// @brief Implementation of Objectss class as defined in AesopObjects.h

#include "AesopObjects.h"

namespace ae {
   /// @class Objects
   ///
   /// A set of named objects that exist in a particular problem.

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
      return it == mObjects.end() ? "" : it->second;
   }
};
