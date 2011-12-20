/// @file AesopDomain.cpp
/// @brief Implementation of Domain class as defined in Aesop.h

#include "Aesop.h"

namespace ae {
   /// @class Domain
   ///
   /// A Domain defines a particular problem-solving world. It provides the
   /// Predicates (adjectives) that describe the world, and the Actions (or
   /// verbs) that can be used to change it.
   ///
   /// Domains also provide some meta-information about the way it describes
   /// the world - its requirements. Different requirements imply different
   /// 'features' the Domain can boast. The requirements supported by Aesop are
   /// listed below:
   /// <ul>
   ///   <li>
   ///      <b>goap:</b> The simplest requirement. <b>goap</b> limits the
   ///      number of parameters for each Action and Predicate to 1. If no
   ///      requirements are defined, <b>goap</b> is used. <i>Note: <b>goap</b>
   ///      is not part of standard PDDL.</i>
   ///   </li>
   ///   <li>
   ///      <b>strips:</b> This requirement implements classic STRIPS-like
   ///      planning. Actions and Predicates can have any number of parameters,
   ///      but more advanced features are not available.
   ///   </li>
   ///   <li>
   ///      <b>typing:</b> With <b>typing</b> enabled, objects in a problem can
   ///      belong to a type from a set defined in the Domain. Without this
   ///      requirement, all objects are of type 'object'.
   ///   </li>
   ///   <li>
   ///      <b>equality:</b> This requirement simply pre-defines an equality
   ///      predicate named '='.
   ///   </li>

   Domain::Domain(std::string name)
   {
      mName = name;
      mTypes.insert("object");
   }

   Domain::~Domain()
   {
   }

   void Domain::addRequirement(requirement req)
   {
      mRequirements.insert(req);
   }

   bool Domain::hasRequirement(requirement req) const
   {
      return mRequirements.find(req) != mRequirements.end();
   }

   void Domain::addType(const char *type)
   {
      if(!hasRequirement(typing))
         return;
      mTypes.insert(type);
   }

   bool Domain::hasType(const char *type) const
   {
      return mTypes.find(type) != mTypes.end();
   }

   Action *Domain::addAction(std::string name, float cost)
   {
      mActions[name] = Action(name, cost);
      return &mActions[name];
   }
};
