/// @file AesopPredicates.h
/// @brief Definition of Predicates class.

#ifndef _AE_PREDICATES_H_
#define _AE_PREDICATES_H_

#include "AesopRequirements.h"
#include "AesopTypes.h"

#include <map>
#include <string>

namespace ae {
   /// @brief A set of Predicates defined in a particular planning problem.
   /// @ingroup Aesop
   class Predicates {
      struct Predicate;
      typedef std::pair<std::string, std::string> parameter;
      typedef std::vector<parameter> paramlist;
      typedef std::map<std::string, Predicate> predicatemap;

   public:
      /// @brief Add a new predicate.
      /// @param name The name of the predicate.
      void add(Predicate &newpred);

      /// @brief Construct a new Predicate.
      /// @param name Name of the new Predicate.
      /// @return A fresh Predicate object.
      Predicate create(std::string name);

      /// @brief Do we have a predicate of the given name?
      /// @param name Look for predicates with this name.
      /// @return True if we have a predicate with that name, false if not.
      bool has(std::string name) const;

      /// @brief Get the type of a named object.
      /// @param name Name of the object to get the type of.
      /// @return The object's type as a new string.
      std::string typeof(std::string name) const;

      /// @brief Get our Requirements object.
      /// @return Handle of our Requirements.
      const Requirements &getRequirements() const { return mRequirements; }

      /// @brief Default constructor.
      /// @param reqs  Requirements we must adhere to.
      /// @param types Types to validate our predicate parameters.
      Predicates(const Requirements &reqs = DefaultRequirements,
         const Types &types = NoTypes);

      /// @brief Get our types object.
      /// @return Handle of our types.
      const Types &getTypes() const { return mTypes; }

      /// @brief Default destructor.
      ~Predicates();

   protected:
      /// @brief Alternate name for has method.
      /// @see Predicates::has
      bool have(std::string name) const { return has(name); }

   private:
      /// @brief Store a Predicate.
      struct Predicate
      {
         friend class Predicates;

         Predicate(std::string n)
            : name(n)
         {
         }

         Predicate()
         { Predicate(""); }

         /// @brief Modulus adds new parameters.
         Predicate & operator% (std::string p)
         {
            params.push_back(std::make_pair(p, ""));
            return *this;
         }

         /// @brief Division sets the type of previous parameters.
         Predicate & operator/ (std::string t)
         {
            params.back().second = t;
            return *this;
         }

         unsigned int getNumParams()
         { return params.size(); }

      private:
         std::string name;
         paramlist params;
      };

      /// @brief Types to validate predicate parameters.
      const Types &mTypes;

      /// @brief Requirements to adhere to.
      const Requirements &mRequirements;

      /// @brief Set of defined Predicates.
      predicatemap mPredicates;
   };
};

#endif
