// @file AesopDemo.cpp
// @brief A small test application for the Aesop library.

#include <stdio.h>
#include <stdarg.h>

#include "AesopDemo.h"
#include "AesopObjects.h"
#include "AesopPredicates.h"

/*void printPlan(ae::Plan plan)
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
}*/

int main(int argc, char **argv)
{
   // Define the types we will use.
   ae::Types types;
   types.add("physob");
   types.add("place");
   types.add("person", "physob");

   // Create predicates that describe our world physics.
   ae::Predicates preds;

   preds.create("at");
   preds.parameter("where", "place");
   preds.add();

   preds.create("adjacent");
   preds.parameter("a", "place");
   preds.parameter("b", "place");
   preds.add();

   preds.create("hungry");
   preds.add();

   preds.create("money");
   preds.add();

   // Create some objects.
   ae::Objects objects(types);
   objects.add("roomA", "place");
   objects.add("roomB", "place");
   objects.add("roomC", "place");

   return 0;
}
