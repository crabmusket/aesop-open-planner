/// @file AesopContext.h
/// Definition of Context class.

#ifndef _AE_CONTEXT_H_
#define _AE_CONTEXT_H_

#include <stdio.h>
#include <time.h>
#include "AesopProblem.h"

namespace Aesop {
   /// Provides logging and profiling for Aesop functions.
   /// @ingroup Aesop
   class Context {
   public:
      virtual void success() = 0;
      virtual void failure() = 0;
      virtual void toClosed(unsigned int ID) = 0;
      //virtual void newState(const Problem::openstate &s) = 0;
      virtual void beginPlanning() = 0;
      virtual void beginIteration() = 0;
      virtual void endIteration() = 0;
      virtual void endPlanning() = 0;
   protected:
   private:
   };

   /// Context that does nothing.
   class NullContext : public Context {
   public:
      virtual void success() {}
      virtual void failure() {}
      virtual void toClosed(unsigned int ID) {}
      //virtual void newState(const Problem::openstate &s) {}
      virtual void beginPlanning() {}
      virtual void beginIteration() {}
      virtual void endIteration() {}
      virtual void endPlanning() {}
   };
};

#endif
