// @file AesopDemo.cpp
// @brief A small test application for the Aesop library.

#include <stdio.h>
#include <stdarg.h>

#include "AesopDemo.h"
#include "Aesop.h"

void printPlan(ae::Plan plan)
{
   ae::Plan::const_iterator it;
   printf("The Plan:\n");
   for(it = plan.begin(); it != plan.end(); it++)
   {
      printf("   %s", it->ac->getName().c_str());
      if(it->params.size())
      {
         ae::paramlist::const_iterator pl;
         for(pl = it->params.begin(); pl != it->params.end(); pl++)
            printf(" %c", *pl);
      }
      putchar('\n');
   }
}

int main(int argc, char **argv)
{
   // Create several Predicate names.
   ae::PName at = "at";
   ae::PName hungry = "hungry";
   ae::PName money = "money";

   // Boolean predicate values.
   ae::PVal ptrue = 1;
   ae::PVal pfalse = 0;

   // Three location names.
   ae::PVal loc1 = 'A';
   ae::PVal loc2 = 'B';
   ae::PVal loc3 = 'C';

   // Create a WorldState to represent our initial state.
   ae::WorldState start;
   start.setPredicate(at, loc1);
   start.setPredicate(money, pfalse);

   // Create another WorldState which will be our goal.
   ae::WorldState goal;
   goal.setPredicate(hungry, pfalse);

   // Action to buy food from loc2.
   //   Required: we are at loc2 and have money
   //   Outcome:  we have no money and are not hungry
   ae::DefaultAction aOrder("Buy food");
   aOrder.addRequired(at, loc2);
   aOrder.addRequired(money, ptrue);
   aOrder.addSet(money, pfalse);
   aOrder.addSet(hungry, pfalse);

   // Action to take money from loc3.
   //   Required: we are at loc3 and have no money
   //   Outcome:  we have money
   ae::DefaultAction aTake("Take money");
   aTake.addRequired(at, loc3);
   aTake.addRequired(money, pfalse);
   aTake.addSet(money, ptrue);

   // Movement action.
   //   Required: we are at location given by param 0
   //   Outcome: we are at location given by param 1
   MoveAction aMove("Move");
   aMove.addRequiredParam(at, 0);
   aMove.addSetParam(at, 1);

   // Bundle these actions into an ActionSet.
   ae::ActionSet actions;
   actions.push_back(&aMove);
   actions.push_back(&aTake);
   actions.push_back(&aOrder);

   // Construct a logger to keep track of the planning process.
   AesopDemoContext context(false);

   // Make a plan to get from 'start' to 'goal'.
   ae::Planner planner(&start, &goal, &actions);
   printf("Planning with normal behaviour.\n");
   if(planner.plan(&context))
   {
      const ae::Plan plan = planner.getPlan();
      printPlan(plan);
   }
   else
   {
      printf("No plan found to satisfy goal!\n");
   }
   putchar('\n');

   // Make a plan for a flying character.
   AesopDemoContext fcontext(true);
   printf("Planning with flying behaviour!\n");
   if(planner.plan(&fcontext))
   {
      const ae::Plan plan = planner.getPlan();
      printPlan(plan);
   }
   else
   {
      printf("No plan found to satisfy goal!\n");
   }
   putchar('\n');

   // Now make a short plan where we start off with money.
   start.setPredicate(money, ptrue);
   printf("Planning with money in our pocket.\n");
   if(planner.plan(&context))
   {
      const ae::Plan plan = planner.getPlan();
      printPlan(plan);
   }
   else
   {
      printf("No plan found to satisfy goal!\n");
   }
   putchar('\n');

   return 0;
}

/// @class AesopDemoLogger
///
/// This class demonstrates the use of the AesopContext interface. We simply
/// print out all log events, while providing some additional functionality
/// to allow planning with two different character types - flying and walking.
/// While this seems like a pathfinding issue, the idea is to demonstrate
/// the possibility of changing the planner's behaviour with user-defined
/// parameters.

/// In this simple implementation, we use vprintf to write the event message
/// to stdout.
void AesopDemoContext::logEvent(const char *fmt, ...)
{
   /*
   va_list args;
   va_start(args, fmt);
   vprintf(fmt, args);
   putchar('\n');
   va_end(args);
   */
}

AesopDemoContext::AesopDemoContext(bool canFly)
{
   mFlying = canFly;
}

AesopDemoContext::~AesopDemoContext()
{
}

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
/// Fill in permutations of starting locations as appropriate.
void MoveAction::getParams(ae::AesopContext *ctx, const ae::paramlist &plist, ae::paramset &pset) const
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
      // But not if we're flying!
      if(dctx->canFly())
      {
         pset.push_back(ae::paramlist(mNumParams));
         pset.back()[0] = 'C';
         pset.back()[1] = 'A';
      }
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
      // But not if we're flying!
      if(dctx->canFly())
      {
         pset.push_back(ae::paramlist(mNumParams));
         pset.back()[0] = 'A';
         pset.back()[1] = 'C';
      }
      break;
   }
}
