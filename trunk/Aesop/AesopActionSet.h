/// @file AesopActionSet.h
/// @brief Definition of ActionSet class.

#ifndef _AE_ACTIONSET_H_
#define _AE_ACTIONSET_H_

#include "Aesop.h"
#include "AesopPredicates.h"

namespace ae {
   /// @brief A set of Actions defined in a particular planning problem.
   /// @ingroup Aesop
   class ActionSet {
      struct Action;
      typedef std::pair<std::string, std::string> parameter;
      typedef std::vector<parameter> paramlist;
      typedef std::map<std::string, Action> actionmap;

   public:
      /// @brief Add a new Action.
      /// @param newac The new Action to add.
      void add(Action &newac);

      /// @brief Construct a new Action.
      /// @param name Name of the new Action.
      /// @return A fresh Action object.
      Action create(std::string name);

      /// @brief Do we have a Action of the given name?
      /// @param name Look for Actions with this name.
      /// @return True if we have a Action with that name, false if not.
      bool has(std::string name) const;

      /// @brief Get the type of a named object.
      /// @param name Name of the object to get the type of.
      /// @return The object's type as a new string.
      std::string typeof(std::string name) const;

      /// @brief Get our types object.
      /// @return Handle of our types.
      const Predicates &getPredicates() const { return mPredicates; }

      /// @brief Get the Requirements from our Predicates.
      /// @return Handle to our Requirements.
      const Requirements &getRequirements() const { return getPredicates().getRequirements(); }

      /// @brief Default constructor.
      /// @param reqs  Requirements we must adhere to.
      /// @param types Types to validate our Action parameters.
      ActionSet(const Predicates &preds = NoPredicates);

      /// @brief Default destructor.
      ~ActionSet();

   protected:
      /// @brief Alternate name for has method.
      /// @see ActionSet::has
      bool have(std::string name) const { return has(name); }

   private:
      /// @brief Store a Action.
      struct Action
      {
         friend class ActionSet;

         /// @brief Name constructor.
         Action(std::string n)
            : name(n)
         {
         }

         /// @brief Default constructor.
         Action()
         { Action(""); }

         /// @brief Modulus adds new parameters.
         Action & operator% (std::string p)
         {
            params.push_back(std::make_pair(p, ""));
            return *this;
         }

         /// @brief Division sets the type of the last parameter.
         Action & operator/ (std::string t)
         {
            params.back().second = t;
            return *this;
         }

         unsigned int getNumParams()
         { return params.size(); }

      private:
         /// @brief Name of this Action.
         std::string name;
         /// @brief Parameters of this Action.
         paramlist params;
      };

      /// @brief Predicates to validate Action parameters.
      const Predicates &mPredicates;

      /// @brief Set of defined Actions.
      actionmap mActions;
   };
};

#endif
