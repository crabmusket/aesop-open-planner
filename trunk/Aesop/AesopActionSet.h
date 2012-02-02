/// @file AesopActionSet.h
/// @brief Definition of ActionSet class.

#ifndef _AE_ACTIONSET_H_
#define _AE_ACTIONSET_H_

#include "Aesop.h"
#include "AesopPredicates.h"

namespace ae {
   /// @brief A set of Actions defined in a particular planning problem.
   /// @ingroup Aesop
   template<typename preds_t, typename an, typename ap>
   class ActionSet {
   public:
      typedef preds_t preds;
      typedef typename preds_t::pname pname;
      typedef typename preds_t::pparam pparam;
      typedef an aname;
      typedef ap aparam;

      /// @brief Do we have an action of the given name?
      /// @param[in] name Look for actions with this name.
      /// @return True if we have an action with that name, false if not.
      virtual bool has(aname name) const = 0;

      /// @brief Get our Predicates object.
      /// @return Handle of our Predicates.
      const preds &getPredicates() const { return mPredicates; }

      /// @brief Default constructor.
      /// @param[in] preds Set of Predicates that define what our actions can do.
      ActionSet(const preds &p) : mPredicates(p) {}

   protected:
      /// @brief Alternate name for has method.
      /// @see ActionSet::has
      bool have(aname name) const { return has(name); }

   private:
      /// @brief Predicates to validate Action parameters.
      const preds &mPredicates;
   };

   class GOAPActionSet : public ActionSet<Predicates<unsigned int, char>, unsigned int, char> {
   public:
      /// @name Action creation
      /// @{

      /// @brief Create a new action.
      /// @param[in] name Name of the new action to create.
      /// @return This object.
      GOAPActionSet &create(std::string name);

      /// @brief Add a precondition to the action under construction.
      /// @param[in] cond The ID of the predicate that must be set to allow
      ///                 this action.
      /// @param[in] set  Whether the predicate must be set or unset.
      /// @return This object.
      GOAPActionSet &condition(pname cond, bool set);

      /// @brief Add an effect to the action under construction.
      /// @param[in] eff The ID of the predicate this action affects.
      /// @param[in] set Whether to set or unset this predicate.
      /// @return This object.
      GOAPActionSet &effect(pname cond, bool set);

      /// @brief Set the cost of the action we're constructing.
      /// @param[in] cost Cost of the new action.
      /// @return This object.
      GOAPActionSet &cost(float cost);

      /// @brief Add the action that is currently being constructed.
      void add();

      /// @}

      /// @name ActionSet
      /// @{

      bool has(aname name) const;

      /// @}

      /// @brief Default constructor.
      GOAPActionSet(const preds &pr);

      /// @brief Default destructor.
      ~GOAPActionSet();

   protected:
   private:
      /// @brief Stores the details of a GOAP action.
      struct GOAPAction {
         std::string name;
         float cost;
         GOAPAction() : name(""), cost(0.0f) {}
      };

      /// @brief The action under construction.
      GOAPAction mCurrAction;

      /// @brief All actions that have been defined.
      std::vector<GOAPAction> mActions;
   };
};

#endif
