/// @file AesopActionSet.h
/// @brief Definition of ActionSet class.

#ifndef _AE_ACTIONSET_H_
#define _AE_ACTIONSET_H_

#include "Aesop.h"
#include "AesopPredicates.h"

namespace ae {
   struct conditions
   {
      conditions(bool req = true) {}

      conditions & operator% (std::string s)
      { return *this; }

      conditions & operator/ (std::string s)
      { return *this; }
   };

   struct effects
   {
      effects(bool req = true) {}

      effects & operator% (std::string s)
      { return *this; }

      effects & operator/ (std::string s)
      { return *this; }
   };

   /// @brief Store a Action.
   struct Action
   {
      typedef std::pair<std::string, std::string> parameter;
      typedef std::vector<parameter> paramlist;

      /// @brief Name constructor.
      Action(std::string n)
         : mName(n)
      {
      }

      /// @brief Default constructor.
      Action()
      { Action(""); }

      /// @brief Modulus adds new parameters.
      Action & operator% (std::string p)
      {
         mParams.push_back(std::make_pair(p, ""));
         return *this;
      }

      /// @brief Division sets the type of the last parameter.
      Action & operator/ (std::string t)
      {
         mParams.back().second = t;
         return *this;
      }

      /// @brief Addition adds effects and conditions.
      Action & operator+ (conditions &c)
      { return *this; }
      Action & operator+ (effects &c)
      { return *this; }

      /// @brief Get parameter storage.
      paramlist & getParams() { return mParams; }

      /// @brief Get name of this Action.
      std::string & getName() { return mName; }

   private:
      /// @brief Name of this Action.
      std::string mName;
      /// @brief Parameters of this Action.
      paramlist mParams;
   };

   /// @brief A set of Actions defined in a particular planning problem.
   /// @ingroup Aesop
   class ActionSet {
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

      /// @brief Default constructor.
      /// @param reqs  Requirements we must adhere to.
      /// @param types Types to validate our Action parameters.
      ActionSet(const Predicates &preds);

      /// @brief Default destructor.
      ~ActionSet();

   protected:
      /// @brief Alternate name for has method.
      /// @see ActionSet::has
      bool have(std::string name) const { return has(name); }

   private:
      /// @brief Predicates to validate Action parameters.
      const Predicates &mPredicates;

      /// @brief Set of defined Actions.
      actionmap mActions;
   };
};

#endif
