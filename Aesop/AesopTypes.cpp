/// @file AesopTypes.cpp
/// @brief Implementation of Types class as defined in AesopTypes.h

#include "AesopTypes.h"

namespace ae {
   /// @class Types
   ///
   /// This class is a hierarchical set of type names. Type names can be defined
   /// with a parent, which implies that any objects of that type are also of
   /// the parent type.

   /// I think it is desirable to always have an empty type defined. It acts as
   /// a sort of sentinel for null types, though it may lead to undesirable
   /// behaviour in domains with no types. We'll see.
   /// @todo Ensure wisdom of defining a blank type.
   Types::Types(float load)
   {
      if(load > 0.0f && load <= 1.0f)
         mTypes.max_load_factor(load);
      mTypes[""] = "";
   }

   Types::~Types()
   {
   }

   void Types::add(std::string type, std::string parent)
   {
      // If the parent is undefined, bail.
      if(!have(parent))
         return;
      // Associate type with parent.
      mTypes[type] = parent;
   }

   bool Types::has(std::string type) const
   {
      return mTypes.find(type) != mTypes.end();
   }

   bool Types::isOf(std::string type, std::string ancestor) const
   {
      // Check that both type names exist.
      typetable::const_iterator t = mTypes.find(type),
         a = mTypes.find(ancestor);
      if(t == mTypes.end() || a == mTypes.end())
         return false;
      // Everything is of type null.
      if(ancestor.empty())
         return true;
      // Scan the type hierarchy.
      std::string name = type;
      do
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
      } while(!name.empty());
      // If we didn't return true above, we didn't find a match.
      return false;
   }
};
