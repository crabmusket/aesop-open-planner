/// @file AesopDemoActions.cpp
/// @brief Implements MoveAction and FlyAction from AesopDemo.h

#include "AesopDemo.h"

/// @class MoveAction
///
/// A simple implementation of ae::Action. Its purpose is to provide a generic
/// 'move' Action for AesopDemo. It has two parameters, one for the starting
/// location and one for the destination. It fills in the starting parameter
/// based on locations adjacent to the end point. It is simplistically
/// hard-coded to the three locations 'A', 'B' and 'C' used in the demo app.

/// Subclasses of ae::Action are wise to call its constructor with their values
/// of name and cost. They are encouraged to set their own value of mNumParams,
/// as particular to this implementation of an action.
MoveAction::MoveAction(std::string name, float cost)
   : ae::Action(name, cost)
{
   mNumParams = 2;
}

/// Check to see what finishing parameter has been specified by the planner.
/// Fill in permutations of starting locations as appropriate. We can only move
/// between adjacent locations.
void MoveAction::getParams(ae::Context *ctx, const ae::paramlist &plist, ae::paramset &pset) const
{
   AesopDemoContext *dctx = (AesopDemoContext*)ctx;
   pset.clear();
   switch(plist[1])
   {
   case 'A':
      // If we must finish at A, we only have one option: leave from B.
      pset.push_back(ae::paramlist(mNumParams));
      pset.back()[0] = 'B';
      pset.back()[1] = 'A';
      break;
   case 'B':
      // If we finish at B, we may have arrived from A or C.
      pset.push_back(ae::paramlist(mNumParams));
      pset.back()[0] = 'A';
      pset.back()[1] = 'B';
      pset.push_back(ae::paramlist(mNumParams));
      pset.back()[0] = 'C';
      pset.back()[1] = 'B';
      break;
   case 'C':
      // Finishing at C, we must have started at B.
      pset.push_back(ae::paramlist(mNumParams));
      pset.back()[0] = 'B';
      pset.back()[1] = 'C';
      break;
   }
}

/// @class FlyAction
///
/// A simple implementation of ae::Action.

FlyAction::FlyAction(std::string name, float cost)
   : ae::Action(name, cost)
{
   mNumParams = 2;
}

/// This action allows us to move to all locations no matter where we are.
void FlyAction::getParams(ae::Context *ctx, const ae::paramlist &plist, ae::paramset &pset) const
{
   AesopDemoContext *dctx = (AesopDemoContext*)ctx;
   pset.clear();
   switch(plist[1])
   {
   case 'A':
      pset.push_back(ae::paramlist(mNumParams));
      pset.back()[0] = 'B';
      pset.back()[1] = 'A';
      pset.push_back(ae::paramlist(mNumParams));
      pset.back()[0] = 'C';
      pset.back()[1] = 'A';
      break;
   case 'B':
      pset.push_back(ae::paramlist(mNumParams));
      pset.back()[0] = 'A';
      pset.back()[1] = 'B';
      pset.push_back(ae::paramlist(mNumParams));
      pset.back()[0] = 'C';
      pset.back()[1] = 'B';
      break;
   case 'C':
      pset.push_back(ae::paramlist(mNumParams));
      pset.back()[0] = 'B';
      pset.back()[1] = 'C';
      pset.push_back(ae::paramlist(mNumParams));
      pset.back()[0] = 'A';
      pset.back()[1] = 'C';
      break;
   }
}