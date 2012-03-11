/// @file AesopTypes.cpp
/// Implementation of Types class as defined in AesopTypes.h

#include "AesopTypes.h"

namespace Aesop {
   /// @class Types
   ///
   /// This class is a hierarchical set of type names. Type names can be defined
   /// with a parent, which implies that any objects of that type are also of
   /// the parent type.
   ///
   /// I think it is desirable to always have an empty type defined. It acts as
   /// a sort of sentinel for null types, though it may lead to undesirable
   /// behaviour in domains with no types. We'll see.
   /// @todo Ensure wisdom of defining a blank type.

   const Types::typeID Types::NullType = -1;
};
