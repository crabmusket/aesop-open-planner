/// @file AesopFileWriterContext.h
/// Definition of FileWriterContext class.

#ifndef _AE_FILE_WRITER_CONTEXT_H_
#define _AE_FILE_WRITER_CONTEXT_H_

#include <stdio.h>
#include <time.h>
#include "abstract/AesopContext.h"

namespace Aesop {
   /// Example implementation of Context that writes output to a file.
   class FileWriterContext : public Context {
   public:
      /// @name Context
      /// @{

      virtual void success();
      virtual void failure();
      virtual void toClosed(unsigned int ID);
      //virtual void newState(const Problem::openstate &s);
      virtual void beginPlanning();
      virtual void beginIteration();
      virtual void endIteration();
      virtual void endPlanning();

      /// @}

      /// Default constructor.
      /// @param[in] file File to write output to.
      FileWriterContext(FILE &file);
   protected:
   private:
      /// File handle to write to.
      FILE &mFile;

      /// Time at start of planning.
      clock_t mPlanStart;

      /// Number of iterations performed.
      unsigned int mIters;
   };
};

#endif
