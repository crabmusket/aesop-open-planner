// @file AesopDemo.cpp
// @brief A small test application for the Aesop library.

#include <stdio.h>
#include <stdarg.h>

#include "AesopDemo.h"
#include "AesopWorldState.h"
#include "AesopAction.h"
#include "AesopPlanner.h"

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
   ae::Action aOrder("Buy food");
   aOrder.addCondition(at, loc2);
   aOrder.addCondition(money, ptrue);
   aOrder.addEffect(money, pfalse);
   aOrder.addEffect(hungry, pfalse);

   // Action to take money from loc3.
   //   Required: we are at loc3 and have no money
   //   Outcome:  we have money
   ae::Action aTake("Take money");
   aTake.addCondition(at, loc3);
   aTake.addCondition(money, pfalse);
   aTake.addEffect(money, ptrue);

   // Movement action.
   //   Required: we are at location given by param 0
   //   Outcome: we are at location given by param 1
   MoveAction aMove("Move");
   aMove.addConditionParam(at, 0);
   aMove.addEffectParam(at, 1);

   // Flying movement action.
   //   Required: we are at location given by param 0
   //   Outcome: we are at location given by param 1
   FlyAction aFly("Fly", 1.5f);
   aFly.addConditionParam(at, 0);
   aFly.addEffectParam(at, 1);

   // Bundle these actions into an ActionSet.
   ae::ActionSet actions;
   actions.add(&aMove);
   actions.add(&aTake);
   actions.add(&aOrder);

   // Construct a logger to keep track of the planning process.
   AesopDemoContext context;

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
   actions.add(&aFly);
   printf("Planning with flying behaviour!\n");
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

   // Now reduce the cost of flying (i.e., make it more preferable).
   actions.add(&aFly, 0.5f);
   printf("Planning when we prefer to fly.\n");
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

/// @class AesopDemoContext
/// @ingroup AesopDemo
///
/// This class demonstrates the use of the Context interface. We simply
/// print all log events to stdout.

/// In this simple implementation, we use vprintf to write the event message
/// to stdout.
void AesopDemoContext::logEvent(const char *fmt, ...)
{
   va_list args;
   va_start(args, fmt);
   vprintf(fmt, args);
   putchar('\n');
   va_end(args);
}

AesopDemoContext::AesopDemoContext()
{
}

AesopDemoContext::~AesopDemoContext()
{
}
