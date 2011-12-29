/// @file AesopObjects.h
/// @brief Definition of Objects class.

#ifndef _AE_OBJECTS_H_
#define _AE_OBJECTS_H_

#include "AesopTypes.h"

#include <map>

namespace ae {
   /// @brief A set of objects defined in a particular planning problem.
   /// @ingroup Aesop
   class Objects {
   public:
      /// @brief Add a new object.
      /// @param name The name of the new object.
      /// @param type The type of the object.
      void add(std::string name, std::string type = "");

      /// @brief Do we have an object of the given name?
      /// @param name Look for objects with this name.
      /// @return True if we have an object with that name, false if not.
      bool has(std::string name) const;

      /// @brief Get the type of a named object.
      /// @param name Name of the object to get the type of.
      /// @return The object's type as a new string.
      std::string typeof(std::string name) const;

      /// @brief Default constructor.
      /// @param types Types set to validate objects.
      Objects(const Types &types = NoTypes);

      /// @brief Default destructor.
      ~Objects();

   protected:
      /// @brief Alternate name for has method.
      /// @see Objects::has
      bool have(std::string name) const { return has(name); }

   private:
      /// @brief Types that validate our objects.
      const Types &mTypes;

      /// @brief Internal storage. Maps object names to type names.
      typedef std::map<std::string, std::string> objectmap;

      /// @brief Map of defined objects and their types.
      objectmap mObjects;
   };
};

#endif
