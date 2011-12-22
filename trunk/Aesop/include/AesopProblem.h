/// @file AesopProblem.h
/// @brief Definition of Problem class.

#ifndef _AE_PROBLEM_H_
#define _AE_PROBLEM_H_

#include "Aesop.h"
#include "AesopDomain.h"
#include "AesopWorldState.h"

namespace ae {
   /// @brief Represents a problem instance within a given Domain.
   /// @ingroup Aesop
   class Problem {
   public:
      /// @brief A Problem only exists within a Domain!
      Problem(const Domain &d);

      /// @brief Default destructor.
      ~Problem();

      /// @brief Add a named object to this problem definition.
      /// @param[in] name The name of the object to add.
      /// @param[in] type The type of the object. Defaults to "object" as per PDDL.
      void addObject(const char *name, const char *type = "object");

   protected:
   private:
      /// @brief A set of object names.
      typedef std::set<std::string> objectset;
      /// @brief Maps a type name to an objectset.
      typedef std::map<std::string, objectset> objectmap;

      /// @brief The Domain that we lie within.
      const Domain *mDomain;

      /// @brief Stores all the objects in this problem.
      objectmap mObjects;

      /// @brief The initial state of this Problem.
      WorldState mInit;
      /// @brief The goal state of this Problem.
      WorldState mGoal;
   };
};

#endif
