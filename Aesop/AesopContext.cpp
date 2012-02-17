/// @file AesopContext.h
/// @brief Definition of Context class.

#include <stdio.h>
#include "AesopContext.h"

namespace Aesop {
   FileWriterContext::FileWriterContext(FILE &file)
      : mFile(file)
   {
   }

   void FileWriterContext::success()
   {
      fprintf(&mFile, "Success: current state matches goal state.\n");
   }

   void FileWriterContext::failure()
   {
      fprintf(&mFile, "Failure: open list is empty.\n");
   }

   void FileWriterContext::toClosed(unsigned int ID)
   {
   }

   void FileWriterContext::newState(const Problem::openstate &s)
   {
   }
};
