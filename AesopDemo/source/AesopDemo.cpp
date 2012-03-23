// @file AesopDemo.cpp
// A small test application for the Aesop library.

#include <stdio.h>
#include <stdarg.h>

#include "AesopDemo.h"
#include "Aesop.h"

using namespace Aesop;

void printPlan(Plan plan)
{
   Plan::const_iterator it;
   printf("The Plan:\n");
   for(it = plan.begin(); it != plan.end(); it++)
   {
      printf("   %s", it->ac->getName().c_str());
      if(it->params.size())
      {
         objects::const_iterator pl;
         for(pl = it->params.begin(); pl != it->params.end(); pl++)
            printf(" %c", *pl);
      }
      putchar('\n');
   }
}

int main(int argc, char **argv)
{
   // Create several Predicate names.
   enum {
      at,
      money,
      hungry,
      adjacent,
   };

   // Boolean predicate values.
   PVal ptrue = 't';
   PVal pfalse = 'f';

   // Three location names.
   PVal loc1 = 'A';
   PVal loc2 = 'B';
   PVal loc3 = 'C';

   // Action to buy food from loc2.
   Action aOrder("Buy food");
   aOrder.condition(Fact(at), Equals, loc2);      // Required: at() -> loc2
   aOrder.condition(Fact(money), Equals, ptrue);  // Required: money() -> true
   aOrder.condition(Fact(hungry), Equals, ptrue); // Required: hungry() -> true
   aOrder.effect(Fact(money), Set, pfalse);       // Effect: money() -> false
   aOrder.effect(Fact(hungry), Set, pfalse);      // Effect: hungry() -> false

   // Action to take money from loc3.
   Action aTake("Take money");
   aTake.condition(Fact(at), Equals, loc3);      // Required: at() -> loc3
   aTake.condition(Fact(money), Equals, pfalse); // Required: money() -> false
   aTake.effect(Fact(money), Set, ptrue);        // Effect: money() -> true

   // Movement action.
   Action aMove("Move");
   aMove.parameters(2);                  // Two parameters to this action, move-from and move-to.
   aMove.condition(ArgsNotEqual);        // Cannot move from x to x.
   aMove.condition(Fact(at), 0, Equals); // Required: at() -> param 0
                                         // Required: adjacent(param 0, param 1) -> true
   //aMove.condition(Fact(adjacent) % Parameter(0) % Parameter(1), Equals, ptrue);
   aMove.effect(Fact(at), Unset);        // Effect: unset at(param 0)
   aMove.effect(Fact(at), 1, Set);       // Effect: at() -> param 1

   // Flying movement action.
   //   Required: we are at location given by param 0
   //   Outcome: we are at location given by param 1
   //FlyAction aFly("Fly", 1.5f);
   //aFly.addRequiredParam(at, 0);
   //aFly.addSetParam(at, 1);

   // Bundle these actions into an ActionSet.
   ActionSet actions;
   actions.add(&aMove);
   actions.add(&aTake);
   actions.add(&aOrder);

   // Construct a logger to keep track of the planning process.
   AesopDemoContext context;

   // Set up some basic domain constants.
   WorldState con;
   con.set(Fact(adjacent) % loc1 % loc2, ptrue); // adjacent(A, B) -> true
   con.set(Fact(adjacent) % loc2 % loc3, ptrue); // adjacent(B, C) -> true
   con.set(Fact(adjacent) % loc3 % loc2, ptrue); // adjacent(C, B) -> true
   con.set(Fact(adjacent) % loc2 % loc1, ptrue); // adjacent(B, A) -> true

   // Create a WorldState to represent our initial state.
   WorldState start(con);
   start.set(Fact(at), loc1);      // at() -> loc1
   start.set(Fact(hungry), ptrue); // hungry() -> false
   start.set(Fact(money), pfalse); // money() -> false

   // Create another WorldState which will be our goal.
   WorldState goal(con);
   goal.set(Fact(hungry), pfalse); // hungry() -> false

   // Make a plan to get from 'start' to 'goal'.
   Planner planner(&start, &goal, &con, &actions);
   planner.addObject(loc1);
   planner.addObject(loc2);
   planner.addObject(loc3);
   printf("Planning with normal behaviour.\n");
   if(planner.plan(&context))
   {
      const Plan plan = planner.getPlan();
      printPlan(plan);
   }
   else
   {
      printf("No plan found to satisfy goal!\n");
   }
   putchar('\n');
   /*
   // Make a plan for a flying character.
   //actions.add(&aFly);
   printf("Planning with flying behaviour!\n");
   if(planner.plan(&context))
   {
      const Plan plan = planner.getPlan();
      printPlan(plan);
   }
   else
   {
      printf("No plan found to satisfy goal!\n");
   }
   putchar('\n');

   // Now reduce the cost of flying (i.e., make it more preferable).
   //actions.add(&aFly, 0.5f);
   printf("Planning when we prefer to fly.\n");
   if(planner.plan(&context))
   {
      const Plan plan = planner.getPlan();
      printPlan(plan);
   }
   else
   {
      printf("No plan found to satisfy goal!\n");
   }
   putchar('\n');
   */
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
   if(mFile)
   {
      va_list args;
      va_start(args, fmt);
      vfprintf(mFile, fmt, args);
      fprintf(mFile, "\n");
      va_end(args);
   }
}

AesopDemoContext::AesopDemoContext()
{
   mFile = fopen("log.txt", "w");
}

AesopDemoContext::~AesopDemoContext()
{
   fclose(mFile);
   mFile = NULL;
}
