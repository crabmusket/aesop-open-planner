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
      for(const_iterator it = begin(); it != end(); it++)
         if(it->second == name)
            return true;
      return false;
   }

   std::string Objects::typeof(std::string name) const
   {
      for(const_iterator it = begin(); it != end(); it++)
         if(it->second == name)
            return it->first;
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
