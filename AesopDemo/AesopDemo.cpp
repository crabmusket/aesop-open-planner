// @file AesopDemo.cpp
// A small test application for the Aesop library.

#include <stdio.h>
#include <stdarg.h>

#include "AesopDemo.h"

#include "AesopSimplePredicates.h"
#include "AesopSimpleActionSet.h"
#include "AesopSimpleWorldState.h"

#include "AesopSimpleTypes.h"
#include "AesopTypedObjects.h"
#include "AesopGOAPPredicates.h"
#include "AesopGOAPWorldState.h"

#include "AesopFileWriterContext.h"
#include "AesopReverseAstar.h"

using namespace Aesop;

void printPlan(const Plan &plan, const ActionSet &actions)
{
   printf("The plan:\n");
   Plan::const_iterator it;
   for(it = plan.begin(); it != plan.end(); it++)
   {
      printf("   %s", actions.repr(it->action).c_str());
      if(it->parameters.size())
      {
         WorldState::paramlist::const_iterator pl;
         for(pl = it->parameters.begin(); pl != it->parameters.end(); pl++)
            printf(" %d", *pl);
      }
      putchar('\n');
   }
}

void complexTest()
{
}

/// Subclass categories!
/// The 'Simple' prefixed classes represent the simplest planning logic that
/// is useful. WorldStates are lists of mutually exclusive boolean states.
/// Actions simply flip the states of these booleans.
/// The 'GOAPS' set of classes are designed to mimic the implementation in
/// F.E.A.R. and provide predicates with a maximum of one parameter each. A
/// predicate can only be instanced with one parameter at a time. For example,
/// if a WorldState contains (at X), and you set (at Y), then (at X) is no
/// longer true.
/// The 'STRIPS' family of actions are basically full planning with arbitrary
/// parameters and stuff.

void STRIPSTest()
{
/*
   // --------------------
   // STEP 1. The Domain.

   // 1.1. Define the types of objects that can exist.
   NamedTypes types;
   types.add("object");
   Types::typeID place = types.add("place");

   // 1.2. Create predicates that describe the physics of our problem.
   STRIPSPredicates preds;

   // A physical object can be at a place
   preds.create("at");
   Predicates::predicateID at = preds.parameter(place);
   preds.add();

   preds.create("box-at");
   Predicates::predicateID boxat = preds.parameter(place);
   preds.add();

   preds.create("high");
   Predicates::predicateID high = preds.add();

   preds.create("have-bananas");
   Predicates::predicateID bananas = preds.add();

   // 1.3. Define actions we can use to modify the world state.
   STRIPSActionSet actions;

   actions.create("move");
   actions.parameter(place);
   actions.parameter(place);
   actons.condition(at).param(0).set();
   actions.effect(at).param(1).set();
   actions.effect(at).param(0).unset();
   actions.add();

   actions.create("move-box");
   actions.parameter(place);
   actions.parameter(place);
   actons.condition(at).param(0).set();
   actons.condition(boxat).param(0).set();
   actions.effect(at).param(1).set();
   actions.effect(boxat).param(1).set();
   actions.effect(at).param(0).unset();
   actions.effect(boxat).param(0).unset();
   actions.add();

   actions.create("climb-box");
   actopns.condition(at).equals(boxat).set();
   actions.condition(high).unset();
   actions.effect(high).set();
   actions.add();

   actions.create("take-bananas");
   actions.condition(high).set();
   actions.condition(bananas).unset();
   actions.effect(bananas).set();
   actions.add();

   // --------------------
   // STEP 2. The Problem.

   // 2.1. Create some objects.
   Objects objects(types);
   Objects::objectID a = objects.add("roomA", place);
   Objects::objectID b = objects.add("roomB", place);
   Objects::objectID c = objects.add("roomC", place);

   // 2.2. Create initial and goal world states.
   STRIPSWorldState init, goal;
   STRIPSWorldState::paramlist l;

   l.push_back(a);
   init.set(at, l);
   init.set(bananasat, l);
   l.clear();

   l.push_back(c);
   init.set(boxat, l);
   l.clear();

   goal.set(bananas);
*/
}

/// Very, very simple planning example using the Simple* class family. Plans on
/// simple boolean predicates with no action parameters.
void simpleTest()
{
   // --------------------
   // STEP 1. The Domain.

   // 1.1. Create predicates that describe the physics of our problem.
   SimplePredicates preds;

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
   SimpleActionSet actions(preds);

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
   SimpleWorldState init(preds), goal(preds);

   init.set(haveTarget);

   goal.set(targetDead);

   // --------------------
   // STEP 3. The Solution.
   Plan plan;
   FileWriterContext context(*stdout);
   if(ReverseAstarSolve(init, goal, actions, NoObjects, plan, context))
      printPlan(plan, actions);
   else
      printf("No valid plan was found.\n");
}

/// Demonstrates planning in a domain similar to the GOAP system used in FEAR.
/// Actions and predicates can have a single parameter each, and additionally
/// objects can have types. Dynamic action costs and filters are used.
void goapTest()
{
   // --------------------
   // STEP 1. The Domain.

   // 1.1. Define types.
   enum {
      Room,
      NumTypes
   };

   SimpleTypes types;
   types.define(NumTypes);

   // 1.2. Define predicates.
   GOAPPredicates preds;

   // 1.3. Define actions.

   // --------------------
   // STEP 2. The Problem.

   // 2.1. Create objects.
   enum {
      roomA,
      roomB,
   };

   TypedObjects objects(types);

   objects.create(roomA, Room);
   objects.create(roomB, Room);

   // 2.2. Define initial and goal world states.
   GOAPWorldState init(preds), goal(preds);

   // --------------------
   // STEP 3. The Solution.
   Plan plan;
   FileWriterContext context(*stdout);
   //if(ReverseAstarSolve(init, goal, actions, objects, plan, context))
      //printPlan(plan, actions);
   //else
      //printf("No valid plan was found.\n");
}

int main(int argc, char **argv)
{
   goapTest();
   return 0;
}
