/// @file Aesop.h
/// Main file for Aesop open planning library.

#ifndef _AE_TYPES_H_
#define _AE_TYPES_H_

#include "AesopConfig.h"

#include <map>
#include <vector>
#include <list>

namespace Aesop {
   /// @addtogroup Aesop
   /// @{

   /// A unique identifier for a predicate.
   typedef unsigned int PName;
   /// The value predicate parameters are allowed to take on.
   typedef unsigned int PParam;
   /// A combination of a predicate and its parameters.
   struct Fact {
      PName name;
      PParam params[2];
      int numParams;
      Fact(PName n = 0, unsigned int nparams = 0, PParam p0 = 0, PParam p1 = 0)
         : name(n), numParams(nparams)
      {
         params[0] = p0;
         params[1] = p1;
      }
      bool operator<(const Fact &other) const
      { return name < other.name; }
   };
   /// Value that a Fact can be mapped to.
   typedef unsigned char PVal;

   /// We represent the world as a series of Fact -> PVal associations.
   typedef std::map<Fact, PVal> worldrep;

   /// Types of requirements an Action can place on a Fact.
   enum ConditionType {
      NoCondition,
      Exists,       ///< Value does not matter as long as the Fact is set to something.
      NotExists,    ///< Fact may not be set at all.
      Equal,        ///< Fact must be equal to the given value.
      NotEqual,     ///< Fact must not be equal to the given value.
      Less,         ///< Fact must be less than the given value.
      Greater,      ///< Fact must be greater than the given value.
      LessEqual,    ///< Fact can be less than or equal to the given value.
      GreaterEqual, ///< Fact must be greater than or equal to the given value.
   };

   /// Types of effects Actions can have.
   enum EffectType {
      NoEffect,
      Set,       ///< The Action sets the Fact to a given value.
      Unset,     ///< The Action unsets knowledge of the Fact.
      Increment, ///< The Action increments the value the Fact is set to.
      Decrement, ///< The Action decrements the value the Fact is set to.
   };

   /// A condition is defined by a type and a value.
   struct Operation {
      ConditionType ctype;
      PVal cvalue;
      EffectType etype;
      PVal evalue;
      Operation()
      {
         ctype = NoCondition;
         etype = NoEffect;
         cvalue = evalue = 0;
      }
   };
   
   /// Map Facts to the Conditions upon them.
   typedef std::map<Fact, Operation> operations;

   /// Mapping of predicates to Action parameter indices.
   typedef std::map<PName, unsigned int> actionparams;
   /// A list of parameter values specific to an ActionEntry.
   typedef std::vector<PVal> paramlist;
   /// A set of paramlist objects used to evaluate a single Action with
   ///        many different parameter lists.
   typedef std::list<paramlist> paramset;
   /// @}
};

#endif
