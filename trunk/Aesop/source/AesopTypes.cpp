/// @file AesopTypes.cpp
/// @brief Implementation of Types class as defined in AesopTypes.h

#include "AesopTypes.h"

namespace ae {
   /// @class Types
   ///
   /// This class is a hierarchical set of type names. Type names can be defined
   /// with a parent, which implies that any objects of that type are also of
   /// the parent type.

   Types::Types(float load)
   {
      if(load > 0.0f && load <= 1.0f)
         mTypes.max_load_factor(load);
   }

   Types::~Types()
   {
   }

   void Types::add(const char *type, const char *parent)
   {
      // If the type is already defined, don't try to overwrite.
      if(!type || have(type))
         return;
      // If the parent is undefined, bail.
      if(parent && !have(parent))
         return;
      mTypes[type] = parent;
   }

   bool Types::has(const char *type) const
   {
      return mTypes.find(type) != mTypes.end();
   }

   bool Types::isOf(const char *type, const char *ancestor) const
   {
      // Everything is a type of null, technically.
      if(!ancestor)
         return true;
      // Check that both type names exist.
      typetable::const_iterator t = mTypes.find(type),
         a = mTypes.find(ancestor);
      if(t == mTypes.end() || a == mTypes.end())
         return false;
      // Scan the type hierarchy.
      std::string name = type;
      while(!name.empty())
      {
         if(!name.compare(ancestor))
            return true;
         else
         {
            typetable::const_iterator it = mTypes.find(name);
            if(it != mTypes.end())
               name = it->second;
            else
               break;
         }
      }
      // If we didn't return true above, we didn't find a match.
      return false;
   }
};
