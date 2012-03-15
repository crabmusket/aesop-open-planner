/// @file Aesop.h
/// Main file for Aesop open planning library.

#ifndef _AE_TYPES_H_
#define _AE_TYPES_H_

#include "AesopConfig.h"

#include <map>
#include <vector>

namespace Aesop {
   /// @addtogroup Aesop
   /// @{

   /// A unique identifier for a predicate.
   typedef unsigned int PName;
   /// The value predicate parameters are allowed to take on.
   typedef unsigned int PParam;
   /// A pair of parameter values.
   struct paramlist {
      PParam p0, p1;
      PParam operator[](int i) const
      {
         if(i == 0) return p0;
         if(i == 1) return p1;
         return 0;
      }
      PParam &operator[](int i)
      {
         if(i == 0) return p0;
         return p1;
      }
   };
#define PARAMS 2
   /// A list of parameter combinations.
   typedef std::vector<paramlist> paramset;
   typedef std::vector<PParam> objects;

   /// A combination of a predicate and its parameters.
   struct Fact {
      PName name;
      paramlist params;
      int numParams;
      Fact(PName n = 0, unsigned int nparams = 0, PParam p0 = 0, PParam p1 = 0)
         : name(n), numParams(nparams)
      {
         params[0] = p0;
         params[1] = p1;
      }
      bool operator<(const Fact &other) const
      { return name < other.name; }
      bool operator==(const Fact &other) const
      { return name == other.name && numParams == other.numParams &&
      params[0] == other.params[0] && params[1] == other.params[1]; }
   };

   /// Value that a Fact can be mapped to in a WorldState.
   typedef unsigned char PVal;

   /// We represent the world as a series of Fact -> PVal associations.
   typedef std::map<Fact, PVal> worldrep;

   /// Types of requirements an Action can place on a Fact.
   enum ConditionType {
      NoCondition,
      IsSet,        ///< Value does not matter as long as the Fact is set to something.
      IsUnset,      ///< Fact may not be set at all.
      Equals,       ///< Fact must be equal to the given value.
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
      int cparam;
      EffectType etype;
      PVal evalue;
      int eparam;
      Operation()
      {
         ctype = NoCondition;
         etype = NoEffect;
         cvalue = evalue = 0;
         cparam = eparam = -1;
      }
   };

   /// Map Facts to the Conditions upon them.
   typedef std::map<Fact, Operation> operations;

   /// @}
};

#endif
