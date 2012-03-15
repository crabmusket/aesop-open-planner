/// @file Aesop.h
/// Main file for Aesop open planning library.

#ifndef _AE_ACTION_H_
#define _AE_ACTION_H_

#include "AesopTypes.h"
#include "AesopContext.h"

namespace Aesop {
   /// An atomic change that can be made to the world state.
   class Action {
   public:
      /// Get predicate->value mapping that we require to be valid.
      const worldrep& getRequired() const { return mRequired; }
      /// Get the predicate->value mapping we apply when executed.
      const worldrep& getSet()      const { return mPostSet; }
      /// Get the names of statements we unset upon execution.
      const pnamelist& getCleared()  const { return mPostClear; }
      /// Get the predicate->parameter mapping that we require.
      const actionparams& getRequiredParams() const { return mRequiredParam; }
      /// Get the predicate->parameter mapping that we set.
      const actionparams& getSetParams() const {return mPostSetParam; }

      /// Add a single statement to our list of required statements.
      /// @param[in] name Name of the predicate the statement refers to.
      /// @param[in] val  Value the predicate is required to take.
      void addRequired(PName name, PVal val);

      /// Add a mapping between a predicate and a parameter.
      /// @param[in] name  Predicate name to map to a parameter.
      /// @param[in] param Index of a parameter to map to.
      void addRequiredParam(PName name, unsigned int param);

      /// Add a single statement to our list of predicates to set after
      ///        execution.
      /// @param[in] name Name of predicate this statement refers to.
      /// @param[in] val  Value this Action changes the predicate to.
      void addSet(PName name, PVal val);

      /// Add a mapping between a predicate and a parameter.
      /// @param[in] name  Predicate name to map to a parameter.
      /// @param[in] param Index of a parameter to map to.
      void addSetParam(PName name, unsigned int param);

      /// Add a single predicate to the list that we unset after
      ///        execution.
      /// @param[in] pred Name of Predicate to add.
      void addClear(PName pred);

      /// Fills in parameters this Action can take based on a given starting
      /// set of parameters.
      /// @param[in]  ctx   A Context object to provide implementation-specific
      ///                   data and abilities.
      /// @param[in]  plist A single list of parameters that is required by a
      ///                   WorldState.
      /// @param[out] pset  A list of paramlist entries describing possible
      ///                   permutations of this Action's parameters, given
      ///                   the values in the starting set.
      virtual void getParams(Context *ctx, const paramlist &plist, paramset &pset) const { pset.clear(); }

      /// Get this Action's friendly name.
      /// @return This Action's name.
      const std::string& getName() const { return mName; }

      /// Get number of parameters.
      /// @return The number of parameters that define an instance of this
      ///         Action.
      unsigned int getNumParams() const { return mNumParams; };

      /// Get the cost of using this Action.
      /// @return This Action's cost.
      float getCost() const { return mCost; }

      /// Default constructor.
      /// @param[in] name   Friendly name for this Action.
      /// @param[in] params The number of variable parameters this Action has.
      /// @param[in] cost   Cost of performing this Action.
      Action(std::string name, float cost = 1.0f);

      /// Default destructor.
      ~Action();

   protected:
      /// Number of parameters we operate on.
      unsigned int mNumParams;

   private:
      /// Friendly name of this Action.
      std::string mName;
      /// Cost of using this Action in a plan.
      float mCost;

      /// Maps predicate names to the values we require for this Action
      ///        to be valid.
      worldrep mRequired;

      /// Maps predicate names to the values they are set to after this Action
      /// executes successfully.
      worldrep mPostSet;
      /// List of predciates that are cleared (unset) after execution.
      pnamelist mPostClear;
      /// Maps predicate names to parameter indices which we require the
      /// predicate to be set to.
      /// For example, if an entry in this map is ("at", 0) then for the Action
      /// to be valid, the "at" predicate must be set to the value of the 0th
      /// parameter to this Action.
      actionparams mRequiredParam;
      /// Maps predicate names to parameter indices which should provide values
      /// for them to be set to.
      /// For example, if an entry in this map is ("at", 1) then the "at"
      /// predicate will be set to whatever value is in this Action's 1st param
      /// when the Action executes.
      actionparams mPostSetParam;
   };

   /// Represents an instance of an Action with a list of defined parameter
   /// values.
   struct ActionEntry {
      /// The Action this entry is an 'instance' of.
      const Action* ac;
      /// Array of parameter values 
      paramlist params;

      /// Default constructor.
      /// @param[in] a Action this ActionEntry is an instance of.
      ActionEntry()
      {
         ac = NULL;
      }
   };

   /// A Plan is a sequence of Actions that take us from one WorldState to
   /// another.
   typedef std::list<ActionEntry> Plan;

   /// An ActionSet is a bunch of Actions that we are allowed to use as well as
   /// multipliers on their cost representing user preferences.
   class ActionSet {
   public:
      /// Redefinition of std::map type as ActionSet.
      typedef std::map<const Action*, float> actionmap;

      /// @name STL
      /// @{
      typedef actionmap::const_iterator const_iterator;
      actionmap::const_iterator begin() const { return mActions.begin(); }
      actionmap::const_iterator end() const { return mActions.end(); }
      /// @}

      /// Add an Action to this set with a given preference multiplier.
      void add(const Action* ac, float pref = 1.0f) { if(pref < 0.0f) pref = 0.0f; mActions[ac] = pref; }
      /// Remove an Action from this set.
      void remove(const Action *ac) { mActions.erase(ac); }
   protected:
   private:
      /// Store a map of Action pointers to preferences.
      actionmap mActions;
   };
};

#endif
