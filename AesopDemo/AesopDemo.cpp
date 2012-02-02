// @file AesopDemo.cpp
// @brief A small test application for the Aesop library.

#include <stdio.h>
#include <stdarg.h>

#include "AesopDemo.h"
#include "AesopObjects.h"
#include "AesopPredicates.h"
#include "AesopWorldState.h"

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

void complexTest()
{
   // --------------------
   // STEP 1. The Domain.

   // 1.1. Define the types of objects that can exist.
   ae::Types types;
   types.add("physob");
   types.add("place");
   types.add("person", "physob");
   types.add("vendor", "physob");
   types.add("money", "physob");
   types.add("food", "physob");

   // 1.2. Create predicates that describe the physics of our problem.
   ae::AesopPredicates preds;

   // A physical object can be at a place
   preds.create("at");
   preds.parameter("who", "physob");
   preds.parameter("where", "place");
   preds.add();

   // Two places can be adjacent
   preds.create("adjacent");
   preds.parameter("a", "place");
   preds.parameter("b", "place");
   preds.add();

   preds.create("hungry");
   preds.parameter("who", "person");
   preds.add();

   preds.create("carrying");
   preds.parameter("who", "person");
   preds.parameter("what", "physob");
   preds.add();

   preds.create("in");
   preds.parameter("a", "physob");
   preds.parameter("b", "physob");
   preds.add();

   // 1.3. Define actions we can use to modify the world state.

   // move person place place
   // pickup person physob
   // eat person food
   // purchase person vendor money physob

   // --------------------
   // STEP 2. The Problem.

   // 2.1. Create some objects.
   ae::Objects objects(types);
   objects.add("roomA", "place");
   objects.add("roomB", "place");
   objects.add("roomC", "place");
   objects.add("me", "person");
   objects.add("sandwich", "food");
   objects.add("machine", "vendor");
   objects.add("coins", "money");

   // 2.2. Create initial and goal world states.
}

void simpleTest()
{
   // --------------------
   // STEP 1. The Domain.

   // 1.1. Create predicates that describe the physics of our problem.
   ae::GOAPPredicates preds;

   enum {
      fireGun,
      gunLoaded,
      gunEquipped,
      haveGun,
      fireTurret,
      mountTurret,
      findTurret,
      meleeAttack,
      haveTarget,
      targetDead,
      NUMPREDS
   };

   // Make room for all predicates.
   preds.size(NUMPREDS);

   // 1.2. Create actions to modify the world state.

   // --------------------
   // STEP 2. The Problem.

   // 2.1. Create initial and goal world states.
   ae::GOAPWorldState init(preds), goal(preds);

   init.set(haveGun, false);
   init.set(haveTarget, true);

   goal.set(targetDead, true);
}

int main(int argc, char **argv)
{
   simpleTest();
   return 0;
}
