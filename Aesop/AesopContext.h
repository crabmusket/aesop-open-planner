/// @file AesopContext.h
/// @brief Definition of Context class.

#ifndef _AE_CONTEXT_H_
#define _AE_CONTEXT_H_

#include <stdio.h>
#include "AesopProblem.h"

namespace Aesop {
   /// @brief Provides logging and profiling for Aesop functions.
   /// @ingroup Aesop
   class Context {
   public:
      virtual void success() {}
      virtual void failure() {}
      virtual void toClosed(unsigned int ID) {}
      virtual void newState(const Problem::openstate &s) {}
   protected:
   private:
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

      /// @}

      /// @brief Default constructor.
      /// @param[in] file File to write output to.
      FileWriterContext(FILE &file);
   protected:
   private:
      /// @brief File handle to write to.
      FILE &mFile;
   };
};

#endif
