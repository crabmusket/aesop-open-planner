/// @file Aesop.h
/// Main file for Aesop open planning library.

#ifndef _AE_TYPES_H_
#define _AE_TYPES_H_

#include "AesopConfig.h"

#include <map>
#include <vector>
#include <cstdarg>

namespace Aesop {
   /// @addtogroup Aesop
   /// @{

   /// A unique identifier for a predicate.
   typedef unsigned int PName;
   /// The value predicate parameters are allowed to take on.
   typedef unsigned int Object;
   /// A list of parameter values.
   typedef std::vector<int> paramlist;
   /// A list of objects.
   typedef std::vector<Object> objects;
   /// A list of object combinations.
   typedef std::vector<objects> paramset;

   /// A combination of a predicate and its parameters.
   struct Fact {
      /// Predicate identifier that this fact refers to.
      PName name;
      /// Parameters of this fact, a list of objects.
      objects params;

      /// Default constructor.
      Fact(Aesop::PName n = 0) : name(n) {}
      /// Default constructor.
      Fact(Aesop::PName n, unsigned int par) : name(n)
      {
         params.resize(par, 0);
      }

      /// Compare Facts based on their predicate ID.
      bool operator<(const Fact &other) const
      { return name < other.name; }
      /// Equality is on predicate and parameters.
      bool operator==(const Fact &other) const
      { return name == other.name && params == other.params; }

      /// Use Fact(pred) % pparam1 % pparam2 % ...; to create a Fact with parameters.
      Fact &operator%(const Object &obj)
      {
         params.push_back(obj);
         return *this;
      }
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

   /// 
   struct Conditions
   {
      paramlist params;
      Conditions &operator%(int p)
      {
         params.push_back(p);
         return *this;
      }
   };

   /// 
   struct Operation {
      ConditionType ctype;
      PVal cvalue;
      int cparam;
      paramlist cargs;
      EffectType etype;
      PVal evalue;
      int eparam;
      paramlist eargs;
      Operation()
      {
         ctype = NoCondition;
         etype = NoEffect;
         cvalue = evalue = 0;
         cparam = eparam = -1;
      }
   };

   /// Map Facts to the Operations upon them.
   typedef std::map<Fact, Operation> operations;

   /// @}
};

#endif
