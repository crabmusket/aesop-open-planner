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
   };
   /// Value that a Fact can be mapped to.
   typedef unsigned char PVal;

   /// We represent the world as a series of Fact -> PVal associations.
   typedef std::map<Fact, PVal> worldrep;

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
