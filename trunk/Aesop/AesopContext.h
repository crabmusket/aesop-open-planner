/// @file AesopContext.h
/// @brief Definition of Context class.

#ifndef _AE_CONTEXT_H_
#define _AE_CONTEXT_H_

#include <stdio.h>
#include <time.h>
#include "AesopProblem.h"

namespace Aesop {
   /// @brief Provides logging and profiling for Aesop functions.
   /// @ingroup Aesop
   class Context {
   public:
      virtual void success() = 0;
      virtual void failure() = 0;
      virtual void toClosed(unsigned int ID) = 0;
      virtual void newState(const Problem::openstate &s) = 0;
      virtual void beginPlanning() = 0;
      virtual void beginIteration() = 0;
      virtual void endIteration() = 0;
      virtual void endPlanning() = 0;
   protected:
   private:
   };

   /// @brief Context that does nothing.
   class NullContext : public Context {
   public:
      virtual void success() {}
      virtual void failure() {}
      virtual void toClosed(unsigned int ID) {}
      virtual void newState(const Problem::openstate &s) {}
      virtual void beginPlanning() {}
      virtual void beginIteration() {}
      virtual void endIteration() {}
      virtual void endPlanning() {}
   };

   /// @brief Example implementation of Context that writes output to a file.
   class FileWriterContext : public Context {
   public:
      /// @name Context
      /// @{

      virtual void success();
      virtual void failure();
      virtual void toClosed(unsigned int ID);
      virtual void newState(const Problem::openstate &s);
      virtual void beginPlanning();
      virtual void beginIteration();
      virtual void endIteration();
      virtual void endPlanning();

      /// @}

      /// @brief Default constructor.
      /// @param[in] file File to write output to.
      FileWriterContext(FILE &file);
   protected:
   private:
      /// @brief File handle to write to.
      FILE &mFile;

      /// @brief Time at start of planning.
      clock_t mPlanStart;

      /// @brief Number of iterations performed.
      unsigned int mIters;
   };
};

#endif
