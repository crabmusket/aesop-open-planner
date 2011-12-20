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
   // Require the use of the equality predicate.
   domain.addRequirement(ae::equality);

   // Add the types relevant to our problem domain.
   domain.addType("room");
   domain.addType("physob");
   // The next four types are subtypes of physob, whereas room and physob are
   // subtypes of object by default.
   domain.addType("money"/*, "physob"*/);
   domain.addType("vending-machine"/*, "physob"*/);
   domain.addType("person"/*, "physob"*/);

   // Define predicates.
   //ae::Predicate *pr;

   // Define adjacency of rooms.
   //pr = domain.addPredicate("adjacent");
   //pr->addParameter("f", "room");
   //pr->addParameter("t", "room");

   // Define an object being in a room.
   //pr = domain.addPredicate("in");
   //pr->addParameter("x", "physob");
   //pr->addParameter("y", "room");

   // Is somebody hungry?
   //pr = domain.addPredicate("hungry");
   //pr->addParameter("w", "person");

   // Do we have food?
   //pr = domain->addPredicate("havefood");
   //pr->addParameter("w", "person");

   // Create some Actions to solve problems with.
   ae::Action *ac;

   // Move Action.
   ac = domain.addAction("move", 1.0f);
   //ac->addParameter("who", "person");
   //ac->addParameter("from", "room");
   //ac->addParameter("to",   "room");
   //ac->addCondition(true, "in", "who", "from");
   //ac->addCondition(false, "in", "who", "to");
   //ac->addCondition(true, "adjacent", "from", "to");
   //ac->addEffect(false, "in", "who", "from");
   //ac->addEffect(true, "in", "who", "to");

   // Take money.

   // Buy food.

   // Eat food.
   //ac = domain.addAction("eat", 1.0f);
   //ac->addParameter("who", "person");
   //ac->addCondition(true, "havefood", "who");
   //ac->addCondition(true, "hungry", "who");
   //ac->addEffect(false, "havefood", "who");
   //ac->addEffect(false, "hungry", "who");

   // Create a Problem within our domain.
   ae::Problem problem(domain);

   // Add our 3 locations.
   problem.addObject("roomA", "room");
   problem.addObject("roomB", "room");
   problem.addObject("roomC", "room");

   // Add our money.
   problem.addObject("money", "money");

   // And our vending machine.
   problem.addObject("vendor", "vending-machine");

   // 

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
