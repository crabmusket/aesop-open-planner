/// @file AesopFileWriterContext.cpp
/// @brief Implementation of FileWriterContext class.

#include <stdio.h>
#include <time.h>
#include "AesopFileWriterContext.h"

namespace Aesop {
   FileWriterContext::FileWriterContext(FILE &file)
      : mFile(file)
   {
      mPlanStart = clock_t();
      mIters = 0;
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

   void FileWriterContext::beginPlanning()
   {
      mPlanStart = clock();
   }

   void FileWriterContext::beginIteration()
   {
      mIters++;
   }

   void FileWriterContext::endIteration()
   {
   }

   void FileWriterContext::endPlanning()
   {
      float planTime = (clock() - mPlanStart) / CLOCKS_PER_SEC * 1000.0f;
      fprintf(&mFile, "Planning finished in %.3fms after %d iterations.\n",
         planTime, mIters);
   }
};
