/// @file AesopActionSet.cpp
/// @brief Implementation of GOAPActionSet class as defined in AesopActionSet.h

#include "AesopActionSet.h"

namespace ae {
   /// @class GOAPGOAPActionSet
   ///
   /// 

   GOAPActionSet::GOAPActionSet(const preds &pr)
      : ActionSet(pr)
   {
   }

   GOAPActionSet::~GOAPActionSet()
   {
   }

   GOAPActionSet &GOAPActionSet::create(std::string name)
   {
      mCurrAction.name = name;
      return *this;
   }

   GOAPActionSet &GOAPActionSet::condition(pname cond, bool set)
   {
      return *this;
   }

   GOAPActionSet &GOAPActionSet::effect(pname eff, bool set)
   {
      return *this;
   }

   void GOAPActionSet::add()
   {
      mActions.push_back(mCurrAction);
   }

   bool GOAPActionSet::has(aname id) const
   {
      return id < mActions.size();
   }
};
