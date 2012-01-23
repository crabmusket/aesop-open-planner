//
// Copyright (C) 2011-2012 by Daniel Buckmaster (dan.buckmaster@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

/// @file Aesop.h
/// @brief Main include file for Aesop open planning library.

#ifndef _AE_AESOP_H_
#define _AE_AESOP_H_

#include <string.h>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>

#include "AesopConfig.h"

namespace ae {
   /// @addtogroup Aesop
   /// @{

   /// @brief Represents the name of a predicate.
   typedef std::string PName;
   /// @brief Represents the value of a predicate.
   typedef unsigned char PVal;
   /// @brief Simply stores a list of predicate names.
   typedef std::vector<PName> pnamelist;
   /// @brief Mapping of predicates to Action parameter indices.
   typedef std::map<PName, unsigned int> actionparams;
   /// @brief A list of parameter values specific to an ActionEntry.
   typedef std::vector<PVal> paramlist;
   /// @brief A set of paramlist objects used to evaluate a single Action with
   ///        many different parameter lists.
   typedef std::list<paramlist> paramset;
   /// @brief Enumerated values of all the requirements Aesop supports. A
   ///        'requirement' is like a feature of a domain, a particular method
   ///        of interaction that it allows.
   enum requirement {
      goap,     ///< Simplest domain, and default if none specified.
      strips,   ///< Basic STRIPS domain.
      equality, ///< Implements the '=' predicate.
      typing,   ///< Objects can have types.
   };

   /// @brief An interface used to log the planning process.
   /// Designed to be implemented by the end-user in a manner particular to
   /// their application and requirements.
   class Context {
   public:
      /// @brief Record an event taking place. Uses printf-like syntax for now.
      /// @param[in] fmt event format string.
      /// @todo Make this function more useful! Also, provide more fine-grained
      ///       logging. Possibly split over multiple methods.
      virtual void logEvent(const char *fmt, ...) = 0;
   protected:
   private:
   };

   /// @}
};

#endif
