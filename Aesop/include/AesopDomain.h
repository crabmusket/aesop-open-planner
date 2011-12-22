/// @file AesopDomain.h
/// @brief Definition of Domain class.

#ifndef _AE_DOMAIN_H_
#define _AE_DOMAIN_H_

#include "Aesop.h"
#include "AesopAction.h"

namespace ae {
   /// @brief Represents a domain in which problems can be solved.
   /// @ingroup Aesop
   class Domain {
   public:
      /// @brief Default constructor.
      Domain(std::string name);
      /// @brief Default destructor.
      ~Domain();

      /// @brief Get the name of this Domain.
      /// @return Constant pointer to this Domain's name.
      const std::string &getName() { return mName; }

      /// @brief Adds a requirement to this Domain.
      /// @param[in] req The requirement to add.
      void addRequirement(requirement req);

      /// @brief Does this Domain include the given requirement?
      /// @param[in] req Requirement to check for.
      /// @return True if the Domain includes the requirement; false if not.
      bool hasRequirement(requirement req) const;

      /// @brief Add a type to this Domain.
      /// @param[in] type Name of the type to add.
      void addType(const char *type);

      /// @brief Does this Domain define the given type name?
      /// @param[in] type Name of the type to check.
      /// @return True if the type is defined in the Domain; false if not.
      bool hasType(const char *type) const;

      /// @brief Add an Action to this Domain.
      /// @param[in] name Name of the new Action.
      /// @param[in] cost Cost of the Action.
      /// @return Pointer to the newly-inserted Action for editing.
      Action *addAction(std::string name, float cost);

   protected:
   private:
      /// @brief A set of requirement IDs.
      typedef std::set<requirement> requirements;
      /// @brief A set of type names.
      typedef std::set<std::string> types;
      /// @brief A list of Actions.
      typedef std::map<std::string, Action> actionset;

      /// @brief The name of this Domain.
      std::string mName;

      /// @brief Store all the requirements this Domain must satisfy.
      requirements mRequirements;

      /// @brief Stores all the types this Domain defines.
      types mTypes;

      /// @brief Actions this Domain is allowed to perform.
      actionset mActions;
   };
};

#endif
