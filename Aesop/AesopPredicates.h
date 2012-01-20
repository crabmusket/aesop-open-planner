/// @file AesopPredicates.h
/// @brief Definition of Predicates class.

#ifndef _AE_PREDICATES_H_
#define _AE_PREDICATES_H_

#include "AesopRequirements.h"
#include "AesopTypes.h"

#include <map>
#include <string>

namespace ae {
   /// @brief Store a Predicate.
   struct Predicate
   {
      typedef std::pair<std::string, std::string> parameter;
      typedef std::vector<parameter> paramlist;

      Predicate(std::string n)
         : mName(n)
      {
      }

      Predicate()
      { Predicate(""); }

      /// @brief Modulus adds new parameters.
      Predicate & operator% (std::string p)
      {
         mParams.push_back(std::make_pair(p, ""));
         return *this;
      }

      /// @brief Division sets the type of previous parameters.
      Predicate & operator/ (std::string t)
      {
         mParams.back().second = t;
         return *this;
      }

      /// @brief Get parameter storage.
      paramlist & getParams() { return mParams; }

      /// @brief Get name of this Predicate.
      std::string & getName() { return mName; }

   private:
      std::string mName;
      paramlist mParams;
   };

   /// @brief A set of Predicates defined in a particular planning problem.
   /// @ingroup Aesop
   class Predicates {
      typedef std::map<std::string, Predicate> predicatemap;

   public:
      /// @brief Add a new predicate.
      /// @param newpred The new Predicate to add.
      void add(Predicate &newpred);

      /// @brief Construct a new Predicate.
      /// @param name Name of the new Predicate.
      /// @return A fresh Predicate object.
      Predicate create(std::string name);

      /// @brief Do we have a predicate of the given name?
      /// @param name Look for predicates with this name.
      /// @return True if we have a predicate with that name, false if not.
      bool has(std::string name) const;

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

      /// @brief Types to validate predicate parameters.
      const Types &mTypes;

      /// @brief Requirements to adhere to.
      const Requirements &mRequirements;

      /// @brief Set of defined Predicates.
      predicatemap mPredicates;
   };

   /// @brief Default list of no predicates.
   const Predicates NoPredicates;
};

#endif
