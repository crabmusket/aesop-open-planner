// @file AesopDemo.cpp
// @brief A small test application for the Aesop library.

#include <stdio.h>
#include <stdarg.h>

#include "AesopDemo.h"
#include "AesopObjects.h"
#include "AesopActionSet.h"

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

   // Create several Predicate names, just for convenience.
   ae::PName at = "at";
   ae::PName adj = "adjacent";
   ae::PName hungry = "hungry";
   ae::PName money = "hasmoney";

   // Define physics in terms of predicates.
   ae::Predicates preds(reqs, types);

   preds.add(ae::Predicate(adj)      // Two places can be adjacent.
      % "loc1" / "place"             //    First parameter must be a place
      % "loc2" / "place");           //    Second is the same

   preds.add(ae::Predicate(at)       // Our actor can be in a place.
      % "loc" / "place");            //    Parameter 'loc' must be a 'place'.

   preds.add(ae::Predicate(hungry)); // Our actor can be hungry. No parameters.

   preds.add(ae::Predicate(money));  // Our actor can posess money.

   // Create a set of Actions to plan with.
   ae::ActionSet actions;

   actions.add(ae::Action("move") // Move action for a person between two locations
      % "from" / "place"          //    Where are we moving from?
      % "to" / "place"            //    Where are we moving to?
      + ae::conditions(1)         // Conditions that must be true:
         % at / "from"            //    we must be at "from"
         % adj / "from" / "to"    //    "from" must be adjacent to "to"
      + ae::effects(1)            // Predicates set by this action:
         % at / "to"              //    "who" is now at "to"
      + ae::effects(0)            // Predicates unset by this action:
         % at / "from");          //    "who" is no longer at "from"

   actions.add(ae::Action("takemoney") // Take the money from room C.
      + ae::conditions(1)
         % at / "roomC"
      + ae::conditions(0)
         % money
      + ae::effects(1)
         % money);

   actions.add(ae::Action("buyfood") // Buy the food from room B.
      + ae::conditions(1)
         % at / "roomB"
      +ae::effects(0)
         % hungry);

   return 0;
}
