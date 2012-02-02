/// @file AesopPredicates.h
/// @brief Definition of Predicates class.

#ifndef _AE_PREDICATES_H_
#define _AE_PREDICATES_H_

#include "AesopTypes.h"

#include <map>
#include <string>
#include <set>

namespace ae {
   /// @brief A set of Predicates defined in a particular planning problem.
   /// @ingroup Aesop
   template<typename n>
   class Predicates {
   public:
      typedef n pname;

      /// @brief Do we have a predicate of the given name?
      /// @param name Look for predicates with this name.
      /// @return True if we have a predicate with that name, false if not.
      virtual bool has(pname name) const = 0;

   protected:
      /// @brief Alternate name for has method.
      /// @see Predicates::has
      bool have(pname name) const { return has(name); }

   private:
   };

   /// @brief A full implementation of the Predicates interface.
   /// @ingroup Aesop
   class AesopPredicates : public Predicates<std::string> {
   public:
      /// @name Predicate construction
      /// @{

      /// @brief Construct a new Predicate.
      /// @param name Name of the new Predicate.
      /// @return This PredicatesInterface object.
      AesopPredicates &create(pname name);

      /// @brief Add a parameter to the Predicate under construction.
      /// @param name The name of this parameter.
      /// @param type The type of data this parameter must hold.
      /// @return This PredicatesInterface object.
      AesopPredicates &parameter(pname name, std::string type = "");

      /// @brief Add the Predicate that is currently under construction.
      void add();

      /// @}

      virtual bool has(pname name) const;

      /// @brief Default constructor.
      AesopPredicates(const Types &types = NoTypes);

      /// @brief Default destructor.
      ~AesopPredicates();

   protected:
   private:
      /// @brief Store a Predicate.
      struct Predicate
      {
         typedef std::vector<std::string> paramlist;

         std::string mName;
         paramlist mParams;
         paramlist mTypes;

         Predicate(std::string n)
            : mName(n)
         {
         }

         Predicate()
         { Predicate(""); }
      };

      /// @brief Maps predicate names to Predicate objects.
      typedef std::map<pname, Predicate> predicatemap;

      /// @brief Store our defined Predicates.
      predicatemap mPredicates;

      /// @brief Predicate currently under construction.
      Predicate mCurPred;

      /// @brief Types list to validate our predicates.
      const Types &mTypes;
   };

   /// @brief A limited, optimised Predicate container.
   /// This container cannot store predicates with parameters.
   /// @ingroup Aesop
   class GOAPPredicates : public Predicates<unsigned int> {
   public:
      /// @name Predicate construction
      /// @{

      /// @brief Prepare the object for this many predicate entries.
      /// @param count The expected number of predicates to store.
      void reserve(unsigned int count);

      /// @brief Register a predicate ID for use.
      /// @param id Integer value of the predicate to use.
      void add(pname id);

      /// @}

      virtual bool has(pname id) const;

      /// @brief Default constructor.
      GOAPPredicates();

      /// @brief Default destructor.
      ~GOAPPredicates();

   protected:
   private:
      /// @brief List of predicate IDs that are used.
      typedef std::vector<char> predicatelist;

      /// @brief Store our defined Predicates.
      predicatelist mPredicates;
   };
};

#endif
