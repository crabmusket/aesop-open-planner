/// @file AesopRequirements.h
/// @brief Definition of Requirements struct.

#ifndef _AE_REQUIREMENTS_H_
#define _AE_REQUIREMENTS_H_

namespace ae {
   /// @brief A description of the limits of a planning domain.
   /// @ingroup Aesop
   struct Requirements {
      /// @name Types
      /// @{

      /// @brief Do we allow users to define arbitrary types?
      bool typing;

      /// @}

      /// @name Actions
      /// @{

      /// @brief Maximum number of parameters for an Action.
      /// If set to 0, no parameters are allowed. If set to any negative value,
      /// an unlimited number are allowed.
      int maxActionParams;
      /// @brief Do we allow Actions to use their parameters in their 
      bool actionParamsInConditions;

      /// @}

      /// @name Predicates
      /// @{

      /// @brief Maximum number of predicates allowed.
      int maxPredicates;
      /// @brief Do we allow predicates to have parameters?
      bool predicateParameters;
      /// @brief Can predicates take on real values, or only booleans?
      bool predicateRealValues;

      /// @}
   };

   /// @brief Default requirements for Aesop.
   const Requirements DefaultRequirements = {
      true, // Types enabled
      -1,   // Any number of parameters per Action
      true, // Parameters can appear in Action conditions
      -1,   // Any number of predicates allowed
      true, // Predicates can have parameters
      true  // Predicates can take on real values
   };

   /// @brief A Requirements that defines the simple GOAP domain.
   const Requirements GOAPRequirements = {
      false, // No typing
      1,     // One parameter per Action
      false, // Parameter cannot appear in Action conditions
      -1,    // Any number of predicates allowed
      false, // No parameters for predicates
      true   // Predicates can take on real values
   };

   /// @brief A Requirements for PDDL's STRIPS domain.
   const Requirements STRIPSRequirements = {
      true, // Types enabled
      -1,   // Any number of parameters per Action
      true, // Parameters can appear in Action conditions
      -1,   // Any number of predicates allowed
      true, // Predicates can have parameters
      false // Predicates can only be true or false
   };
};

#endif
