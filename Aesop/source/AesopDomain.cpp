/// @file AesopDomain.cpp
/// @brief Implementation of Domain class as defined in Aesop.h

#include "Aesop.h"

namespace ae {
   /// @class Domain
   ///
   /// 

   Domain::Domain()
   {
   }

   Domain::~Domain()
   {
   }

   void Domain::addRequirement(requirement req)
   {
      mRequirements.insert(req);
   }

   bool Domain::hasRequirement(requirement req)
   {
      return mRequirements.find(req) != mRequirements.end();
   }
};
