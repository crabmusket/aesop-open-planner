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

void complexTest()
{
   // --------------------
   // STEP 1. The Domain.

   // 1.1. Define the types of objects that can exist.
   ae::Types types;
   types.add("physob");
   types.add("place");
   types.add("person", "physob");

   // 1.2. Create predicates that describe the physics of our problem.
   ae::Predicates preds;

   preds.create("at");
   preds.parameter("where", "place");
   preds.add();

   preds.create("adjacent");
   preds.parameter("a", "place");
   preds.parameter("b", "place");
   preds.add();

   preds.create("hungry").add();

   preds.create("money").add();

   // 1.3. Define actions we can use to modify the world state.

   // --------------------
   // STEP 2. The Problem.

   // 2.1. Create some objects.
   ae::Objects objects(types);
   objects.add("roomA", "place");
   objects.add("roomB", "place");
   objects.add("roomC", "place");

   // 2.2. Create initial and goal world states.
}

void simpleTest()
{
   // --------------------
   // STEP 1. The Domain.

   // 1.1. Create predicates that describe the physics of our problem.
   ae::GOAPPredicates preds;

   preds.create("fireGun").add();
   preds.create("gunLoaded").add();
   preds.create("gunEquipped").add();
   preds.create("haveGun").add();
   preds.create("fireTurret").add();
   preds.create("mountTurret").add();
   preds.create("findTurret").add();
   preds.create("meleeAttack").add();
   preds.create("haveTarget").add();
   preds.create("targetDead").add();

   // 1.2. Create actions to modify the world state.

   // --------------------
   // STEP 2. The Problem.

   // 2.1. Create initial and goal world states.
}

int main(int argc, char **argv)
{
   simpleTest();
   return 0;
}
