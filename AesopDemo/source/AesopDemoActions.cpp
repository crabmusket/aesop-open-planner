/// @file AesopDemoActions.cpp
/// Implements MoveAction and FlyAction from AesopDemo.h

#include "AesopDemo.h"

/// @class MoveAction
/// @ingroup AesopDemo
///
/// A simple implementation of Action. Its purpose is to provide a generic
/// 'move' Action for AesopDemo. It has two parameters, one for the starting
/// location and one for the destination. It fills in the starting parameter
/// based on locations adjacent to the end point. It is simplistically
/// hard-coded to the three locations 'A', 'B' and 'C' used in the demo app.

/// Subclasses of Action are wise to call its constructor with their values
/// of name and cost. They are encouraged to set their own value of mNumParams,
/// as particular to this implementation of an action.
MoveAction::MoveAction(std::string name, float cost)
   : Action(name, cost)
{
   mNumParams = 2;
}

FlyAction::FlyAction(std::string name, float cost)
   : Action(name, cost)
{
   mNumParams = 2;
}
