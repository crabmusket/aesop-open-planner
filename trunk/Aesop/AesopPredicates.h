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
   template<typename pname, typename paramname, typename paramtype, typename pval>
   class PredicatesInterface {
   public:
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

   /// @brief A full implementation of the PredicatesInterface.
   /// @ingroup Aesop
   class Predicates : public PredicatesInterface<std::string, std::string, std::string, bool> {
   public:
      /// @name Predicate construction
      /// @{

      /// @brief Construct a new Predicate.
      /// @param name Name of the new Predicate.
      /// @return This PredicatesInterface object.
      Predicates &create(std::string name);

      /// @brief Add a parameter to the Predicate under construction.
      /// @param name The name of this parameter.
      /// @param type The type of data this parameter must hold.
      /// @return This PredicatesInterface object.
      Predicates &parameter(std::string name, std::string type = "");

      /// @brief Add the Predicate that is currently under construction.
      void add();

      /// @}

      bool has(std::string name) const;

      /// @brief Default constructor.
      Predicates(const Types &types = NoTypes);

      /// @brief Default destructor.
      ~Predicates();

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
      typedef std::map<std::string, Predicate> predicatemap;

      /// @brief Store our defined Predicates.
      predicatemap mPredicates;

      /// @brief Predicate currently under construction.
      Predicate mCurPred;

      /// @brief Types list to validate our predicates.
      const Types &mTypes;
   };

   /// @brief Default list of no predicates.
   const Predicates NoPredicates;

   /// @brief A limited, optimised Predicate container.
   /// This container cannot store predicates with parameters.
   /// @ingroup Aesop
   class GOAPPredicates : public PredicatesInterface<unsigned int, char, char, int> {
   public:
      /// @name Predicate construction
      /// @{

      /// @brief Register a predicate ID for use.
      /// @param id Integer value of the predicate to use.
      void add(unsigned int id);

      /// @}

      bool has(unsigned int id) const;

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
