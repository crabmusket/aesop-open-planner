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
   class PredicatesInterface {
   public:
      /// @name Predicate construction
      /// @{

      /// @brief Construct a new Predicate.
      /// @param name Name of the new Predicate.
      /// @return This PredicatesInterface object.
      virtual PredicatesInterface &create(std::string name) = 0;

      /// @brief Add a parameter to the Predicate under construction.
      /// @param name The name of this parameter.
      /// @param type The type of data this parameter must hold.
      /// @return This PredicatesInterface object.
      virtual PredicatesInterface &parameter(std::string name, std::string type = "") = 0;

      /// @brief Add the Predicate that is currently under construction.
      virtual void add() = 0;

      /// @}

      /// @brief Do we have a predicate of the given name?
      /// @param name Look for predicates with this name.
      /// @return True if we have a predicate with that name, false if not.
      virtual bool has(std::string name) const = 0;

   protected:
      /// @brief Alternate name for has method.
      /// @see Predicates::has
      bool have(std::string name) const { return has(name); }

   private:
   };

   /// @brief A full implementation of the PredicatesInterface.
   /// @ingroup Aesop
   class Predicates : public PredicatesInterface {
   public:
      PredicatesInterface &create(std::string name);
      PredicatesInterface &parameter(std::string name, std::string type = "");
      void add();
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
   class GOAPPredicates : public PredicatesInterface {
   public:
      PredicatesInterface &create(std::string name);
      PredicatesInterface &parameter(std::string name, std::string type = "");
      void add();
      bool has(std::string name) const;

      /// @brief Default constructor.
      GOAPPredicates();

      /// @brief Default destructor.
      ~GOAPPredicates();

   protected:
   private:
      /// @brief List of predicate names.
      typedef std::set<std::string> predicatelist;

      /// @brief Store our defined Predicates.
      predicatelist mPredicates;

      /// @brief Current predicate being created.
      std::string mCurPred;
   };
};

#endif
