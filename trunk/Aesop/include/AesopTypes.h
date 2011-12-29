/// @file AesopTypes.h
/// @brief Definition of Types class.

#ifndef _AE_TYPES_H_
#define _AE_TYPES_H_

#include <string>
#include <unordered_map>

// For VC++2008 compatibility.
//#ifndef std::unordered_map
//#define std::unordered_map std::tr1::unordered_map;
//#endif

namespace ae {
   /// @brief A list of types defined for a planning problem.
   /// @ingroup Aesop
   class Types {
   public:
      /// @brief Define a new type.
      /// @param type   The name of the new type to add.
      /// @param parent The parent type of this type.
      void add(const char *type, const char *parent = NULL);

      /// @brief Is the type defined?
      /// @param type Type name to check.
      /// @return True if the type is defined, false if not.
      bool has(const char *type) const;

      /// @brief Is the former a descendent of the latter?
      /// @param type     The type to verify.
      /// @param ancestor The ancestor type to check for.
      /// @return True if 'type' is a type of 'ancestor'.
      bool isOf(const char *type, const char *ancestor) const;

      /// @brief Default constructor.
      /// @param load The maximum load factor for the internal hash table.
      Types(float load = -1.0f);
      /// @brief Default destructor.
      ~Types();

   protected:
      /// @brief Alternate name for has method.
      /// @see Types::has
      bool have(const char *type) const { return has(type); }

   private:
      /// @brief Maps type names to their parents' names.
      typedef std::tr1::unordered_map<std::string, std::string> typetable;

      /// @brief Sparse array for fast lookups.
      typetable mTypes;
   };
};

#endif
