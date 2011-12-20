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
   // Create a Domain to solve problems in.
   ae::Domain domain("buying-food");

   // Require that objects can have types.
   domain.addRequirement(ae::typing);

   // Add the types relevant to our problem domain.
   domain.addType("room");
   domain.addType("money");
   domain.addType("vending-machine");

   // Create some Actions to solve problems with.
   ae::Action *ac;

   // Move Action.
   ac = domain.addAction("move", 1.0f);

   // Create a Problem within our domain.
   ae::Problem problem(domain);

   // Add our 3 locations.
   problem.addObject("roomA", "room");
   problem.addObject("roomB", "room");
   problem.addObject("roomC", "room");

   // Add our money.
   problem.addObject("themoney", "money");

   // And our vending machine.
   problem.addObject("vendor", "vending-machine");

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
