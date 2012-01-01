/// @file AesopObjects.h
/// @brief Definition of Objects class.

#ifndef _AE_OBJECTS_H_
#define _AE_OBJECTS_H_

#include "AesopTypes.h"

#include <map>
#include <iterator>

namespace ae {
   /// @brief A set of objects defined in a particular planning problem.
   /// @ingroup Aesop
   class Objects {
      /// @brief Internal storage. Maps object names to their types.
      typedef std::map<std::string, std::string> objectmap;
      /// @brief Element type.
      typedef std::pair<std::string, std::string> element;

   public:
      /// @brief Add a new object.
      /// @param name The name of the new object.
      /// @param type The type of the object.
      void add(std::string name, std::string type = "");

      /// @brief Remove an object.
      /// @param name Name of the object to remove.
      void remove(std::string name);

      /// @brief Do we have an object of the given name?
      /// @param name Look for objects with this name.
      /// @return True if we have an object with that name, false if not.
      bool has(std::string name) const;

      /// @brief Get the type of a named object.
      /// @param name Name of the object to get the type of.
      /// @return The object's type as a new string.
      std::string typeof(std::string name) const;

      /// @brief Get our types object.
      /// @return Handle of our types.
      const Types &getTypes() const { return mTypes; }

      /// @name Partial STL interface
      /// @{

      typedef objectmap::const_iterator const_iterator;
      const_iterator begin() const { return mObjects.begin(); }
      const_iterator end() const { return mObjects.end(); }
      unsigned int size(std::string type = "") const;

      /// @brief Iterator that sticks to a particular type and its descendents.
      struct type_iterator : public std::iterator<std::forward_iterator_tag,
         const element, int>
      {
         /// @brief Default constructor
         type_iterator(const_iterator i, const Objects &o, const std::string &t)
            : it(i), objs(o), type(t)
         {
            if(it != objs.end() && !objs.getTypes().isOf(it->second,type))
               ++(*this);
         }

         /// @name Iteration
         /// @{

         type_iterator &operator++()
         {
            it++;
            while(it != objs.end() && !objs.getTypes().isOf(it->second,type))
               it++;
            return *this;
         }

         type_iterator operator++(int)
         {
            type_iterator result(*this);
            ++(*this);
            return result;
         }

         type_iterator &operator--()
         {
            it--;
            while(it != objs.begin() && !objs.getTypes().isOf(it->second,type))
               it--;
            return *this;
         }

         type_iterator operator--(int)
         {
            type_iterator result(*this);
            --(*this);
            return result;
         }

         /// @}

         /// @name Interface
         /// @{

         bool operator==(const type_iterator &other)
         { return it == other.it; }
         bool operator!=(const type_iterator &other)
         { return it != other.it; }

         reference operator*()
         { return *it; }
         const_iterator operator->()
         { return it; }

         /// @}

      private:
         /// @brief Reference to the Objects we iterate over.
         const Objects &objs;
         /// @brief Internal iterator.
         const_iterator it;
         /// @brief Type name to restrict ourselves to.
         std::string type;
      };

      type_iterator begin(std::string type) const { return type_iterator(begin(), *this, type); }
      type_iterator end(std::string type) const { return type_iterator(end(), *this, type); }

      /// @}

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

      /// @brief Map of defined objects and their types.
      objectmap mObjects;
   };
};

#endif
