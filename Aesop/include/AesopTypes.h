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
   /// Represents the name of a predicate.
   typedef unsigned int PName;
   /// Represents the value of a predicate.
   typedef unsigned char PVal;
   /// Method of storing predicates and their values.
   typedef std::map<PName, PVal> worldrep;
   /// Simply stores a list of predicate names.
   typedef std::vector<PName> pnamelist;
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
