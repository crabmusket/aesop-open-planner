// @file AesopDemo.cpp
// @brief A small test application for the Aesop library.

#include <stdio.h>
#include <stdarg.h>

#include "AesopDemo.h"
#include "AesopObjects.h"
#include "AesopPredicates.h"
#include "AesopActionSet.h"
#include "AesopWorldState.h"
#include "AesopReverseAstar.h"

namespace ae = Aesop;

void printPlan(const ae::Plan &plan, const ae::ActionSet &actions)
{
   printf("The plan:\n");
   ae::Plan::const_iterator it;
   for(it = plan.begin(); it != plan.end(); it++)
   {
      printf("   %s", actions.repr(it->action).c_str());
      if(it->parameters.size())
      {
         ae::WorldState::paramlist::const_iterator pl;
         for(pl = it->parameters.begin(); pl != it->parameters.end(); pl++)
            printf(" %d", *pl);
      }
      putchar('\n');
   }
}

void complexTest()
{
}

void STRIPSTest()
{
}

void subSTRIPSTest()
{
   // --------------------
   // STEP 1. The Domain.
/*
   // 1.1. Define the types of objects that can exist.
   ae::NamedTypes types;
   types.add("object");
   ae::Types::typeID place = types.add("place");

   // 1.2. Create predicates that describe the physics of our problem.
   ae::AesopPredicates preds;

   // A physical object can be at a place
   preds.create("at");
   preds.parameter("place");
   preds.add();

   preds.create("box-at");
   preds.parameter("place");
   preds.add();

   preds.create("high");
   ae::Predicates::predicateID high = preds.add();

   // 1.3. Define actions we can use to modify the world state.
   ae::SingleParamActionSet actions;

   actions.create("move");
   actions.parameter(place);
   actions.add();

   actions.create("move-box");
   actions.parameter(place);
   actions.add();

   actions.create("climb-box");
   preds.effect(high);
   actions.add();

   // --------------------
   // STEP 2. The Problem.

   // 2.1. Create some objects.
   ae::Objects objects(types);
   objects.add("roomA", place);
   objects.add("roomB", place);
   objects.add("roomC", place);
*/
   // 2.2. Create initial and goal world states.
}

void simpleTest()
{
   // --------------------
   // STEP 1. The Domain.

   // 1.1. Create predicates that describe the physics of our problem.
   ae::SimplePredicates preds;

   enum {
      gunLoaded,
      gunEquipped,
      haveGun,
      haveMelee,
      meleeEquipped,
      inTurret,
      haveTarget,
      targetDead,
      NUMPREDS
   };

   // Define all predicates.
   preds.define(NUMPREDS);

   // 1.2. Create actions to modify the world state.
   ae::SimpleActionSet actions(preds);

   actions.create("attackRanged");
   actions.condition(haveTarget, true);
   actions.condition(gunLoaded, true);
   actions.condition(targetDead, false);
   actions.effect(targetDead, true);
   actions.effect(gunLoaded, false);
   actions.add();

   actions.create("attackMelee");
   actions.condition(haveTarget, true);
   actions.condition(targetDead, false);
   actions.condition(meleeEquipped, true);
   //actions.condition();
   actions.effect(targetDead, true);
   actions.add();

   actions.create("attackTurret");
   actions.condition(haveTarget, true);
   actions.condition(inTurret, true);
   actions.condition(targetDead, false);
   //actions.condition();
   actions.effect(targetDead, true);
   actions.add();

   actions.create("loadGun");
   actions.condition(gunEquipped, true);
   actions.condition(gunLoaded, false);
   actions.effect(gunLoaded, true);
   actions.add();

   actions.create("drawGun");
   actions.condition(haveGun, true);
   actions.condition(gunEquipped, false);
   actions.effect(gunEquipped, true);
   actions.add();

   actions.create("findGun");
   actions.condition(haveGun, false);
   actions.effect(haveGun, true);
   actions.add();

   actions.create("drawMelee");
   actions.condition(haveMelee, true);
   actions.condition(meleeEquipped, false);
   actions.effect(meleeEquipped, true);
   actions.add();

   actions.create("findMelee");
   actions.condition(haveMelee, false);
   actions.effect(haveMelee, true);
   actions.add();

   actions.create("findTurret");
   actions.condition(inTurret, false);
   actions.effect(inTurret, true);
   //actions.add();

   // --------------------
   // STEP 2. The Problem.

   // 2.1. Create initial and goal world states.
   ae::SimpleWorldState init(preds), goal(preds);

   init.set(haveTarget);

   goal.set(targetDead);

   // --------------------
   // STEP 3. The Solution.
   ae::Plan plan;
   ae::FileWriterContext context(*stdout);
   if(ae::ReverseAstarSolve(init, goal, actions, ae::NoObjects, plan, context))
      printPlan(plan, actions);
   else
      printf("No valid plan was found.\n");
}

int main(int argc, char **argv)
{
   simpleTest();
   return 0;
}
