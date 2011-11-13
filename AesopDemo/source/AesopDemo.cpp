//
//

#include <stdio.h>
#include <stdarg.h>

#include "AesopDemo.h"
#include "Aesop.h"

int main(int argc, char **argv)
{
   // Create several Predicate names.
   ae::PName at = "at";
   ae::PName hungry = "hungry";
   ae::PName money = "money";

   // Boolean predicate values.
   ae::PVal t = 1;
   ae::PVal f = 0;

   // Three location names.
   ae::PVal loc1 = 'a';
   ae::PVal loc2 = 'b';
   ae::PVal loc3 = 'c';

   // Create a WorldState to represent our initial state.
   ae::WorldState start;
   start.setPredicate(at, loc1);

   // Create another WorldState which will be our goal.
   ae::WorldState goal;
   goal.setPredicate(hungry, f);

   // Create some Actions to move between the three locations.
   //   Required: we are in some location
   //   Outcome:  we are in some location adjacent
   ae::Action aMove1("Move 1->2");
   aMove1.addRequired(at, loc1);
   aMove1.addSet(at, loc2);
   ae::Action aMove2("Move 2->3");
   aMove2.addRequired(at, loc2);
   aMove2.addSet(at, loc3);
   ae::Action aMove3("Move 3->2");
   aMove3.addRequired(at, loc3);
   aMove3.addSet(at, loc2);
   ae::Action aMove4("Move 2->1");
   aMove4.addRequired(at, loc2);
   aMove4.addSet(at, loc1);

   // Action to take money from loc3.
   //   Required: we are at loc3 and have no money
   //   Outcome:  we have money
   ae::Action aTake("Take money");
   aTake.addRequired(at, loc3);
   aTake.addSet(money, t);

   // Action to buy food from loc2.
   //   Required: we are at loc2 and have money
   //   Outcome:  we have no money and are not hungry
   ae::Action aOrder("Buy food");
   aOrder.addRequired(at, loc2);
   aOrder.addRequired(money, t);
   aOrder.addSet(money, f);
   aOrder.addSet(hungry, f);

   // Bundle these actions into an ActionSet.
   ae::ActionSet actions;
   actions.push_back(aMove1);
   actions.push_back(aMove2);
   actions.push_back(aMove3);
   actions.push_back(aMove4);
   actions.push_back(aTake);
   actions.push_back(aOrder);

   // Construct a logger to keep track of the planning process.
   AesopDemoLogger logger;

   // Make a plan to get from 'start' to 'goal'.
   ae::Planner planner(&start, &goal, &actions);
   if(planner.plan(&logger))
   {
      const ae::Plan plan = planner.getPlan();
      ae::Plan::const_iterator it;
      printf("The Plan:\n\n");
      for(it = plan.begin(); it != plan.end(); it++)
         printf("%s\n", it->getName().c_str());
   }
   else
   {
      printf("No plan found to satisfy goal!\n");
   }

   return 0;
}

/// @class AesopDemoLogger
///
/// 

/// In this simple implementation, we use vprintf to write the event message
/// to stdout.
void AesopDemoLogger::logEvent(const char *fmt, ...)
{
   va_list args;
   va_start(args, fmt);
   vprintf(fmt, args);
   putchar('\n');
   va_end(args);
}

AesopDemoLogger::AesopDemoLogger()
{
}

AesopDemoLogger::~AesopDemoLogger()
{
}
