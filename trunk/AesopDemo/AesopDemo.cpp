// @file AesopDemo.cpp
// @brief A small test application for the Aesop library.

#include <stdio.h>
#include <stdarg.h>

#include "AesopDemo.h"
#include "AesopObjects.h"
#include "AesopActionSet.h"
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
   // Create some Requirements to give our problem boundaries.
   ae::Requirements reqs = ae::DefaultRequirements;
   reqs.predicateRealValues = false;

   // Define the types we will use.
   ae::Types types;
   types.add("physob");
   types.add("place");
   types.add("person", "physob");

   // Create some objects.
   ae::Objects objects(types);
   objects.add("roomA", "place");
   objects.add("roomB", "place");
   objects.add("roomC", "place");
   objects.add("money", "physob");
   objects.add("vendor", "physob");
   objects.add("me", "person");

   // Create several Predicate names, just for convenience.
   ae::PName at = "at";
   ae::PName hungry = "hungry";
   ae::PName money = "hasmoney";

   // Define physics in terms of predicates.
   ae::Predicates preds(reqs, types);
   preds.add(preds.create(at)     // A physical object can be in a place.
      % "ob" / "physob"           // First parameter 'ob' must be of type 'physob'.
      % "loc" / "place");         // Second parameter 'loc' must be a 'place'.
   preds.add(preds.create(hungry) // A person can be hungry.
      % "who" / "person");        // Just one argument - a 'person'.
   preds.add(preds.create(money)  // A person can posess money.
      % "who" / "person");        // Again, just one argument.

   // Create a set of Actions to plan with.
   ae::ActionSet actions;

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
