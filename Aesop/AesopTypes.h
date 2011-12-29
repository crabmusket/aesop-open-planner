/// @file AesopTypes.h
/// @brief Definition of Types class.

#ifndef _AE_TYPES_H_
#define _AE_TYPES_H_

#include <string>
#include <unordered_map>

namespace ae {
   /// @brief A set of types defined for a planning problem.
   /// @ingroup Aesop
   class Types {
   public:
      /// @brief Define a new type.
      /// @param type   The name of the new type to add.
      /// @param parent The parent type of this type.
      void add(std::string type, std::string parent = "");

      /// @brief Is the type defined?
      /// @param type Type name to check.
      /// @return True if the type is defined, false if not.
      bool has(std::string type) const;

      /// @brief Is the former a descendent of the latter?
      /// @param type     The type to verify.
      /// @param ancestor The ancestor type to check for.
      /// @return True if 'type' is a type of 'ancestor'.
      bool isOf(std::string type, std::string ancestor = "") const;

      /// @brief Default constructor.
      /// @param load The maximum load factor for the internal hash table.
      Types(float load = -1.0f);
      /// @brief Default destructor.
      ~Types();

   protected:
      /// @brief Alternate name for has method.
      /// @see Types::has
      bool have(std::string type) const { return has(type); }

   private:
      /// @brief Maps type names to their parents' names.
#ifdef _WIN32
      typedef std::tr1::unordered_map<std::string, std::string> typetable;
#else
      typedef std::unordered_map<std::string, std::string> typetable;
#endif

      /// @brief Sparse array for fast lookups.
      typetable mTypes;
   };

   /// @brief A default Types with no definitions.
   const Types NoTypes;
};

#endif
