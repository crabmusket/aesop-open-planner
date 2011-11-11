//
//

#include <stdio.h>

#include "AesopDemo.h"
#include "Aesop.h"

int main(int argc, char **argv)
{
   // Create several Predicate names.
   ae::PName at = "at";
   ae::PName hungry = "hungry";
   ae::PName money = "money";

   // Boolean predicate values.
   ae::PVal t = 1;
   ae::PVal f = 0;

   // Three location names.
   ae::PVal loc1 = 'a';
   ae::PVal loc2 = 'b';
   ae::PVal loc3 = 'c';

   // Create a WorldState with a location specified.
   ae::WorldState ws1;
   ws1.setPredicate(at, loc1);

   // Create another WorldState with different data.
   ae::WorldState ws2;
   ws2.setPredicate(at, loc2);
   ws2.setPredicate(money, t);

   // Print out the number of differences between ws1 and ws2.
   printf("Comparison of ws1 and ws2: %d\n", ae::WorldState::comp(ws1, ws2));
   // Should have printed 1, since ws1 and ws2 differ only once, in the value
   // of pred1. (Predicates not set in both states are not counted.)

   // Create some Actions to move between the three locations.
   //   Required: we are in some location
   //   Outcome:  we are in some location adjacent
   ae::Action aMove1;
   aMove1.addRequired(ae::Statement(at, loc1));
   aMove1.addSet(ae::Statement(at, loc2));
   ae::Action aMove2;
   aMove2.addRequired(ae::Statement(at, loc2));
   aMove2.addSet(ae::Statement(at, loc3));
   ae::Action aMove3;
   aMove3.addRequired(ae::Statement(at, loc3));
   aMove3.addSet(ae::Statement(at, loc2));
   ae::Action aMove4;
   aMove4.addRequired(ae::Statement(at, loc2));
   aMove4.addSet(ae::Statement(at, loc1));

   // Action to take money from loc3.
   //   Required: we are at loc3 and have no money
   //   Outcome:  we have money
   ae::Action aTake;
   aTake.addRequired(ae::Statement(at, loc3));
   aTake.addRequired(ae::Statement(money, f));
   aTake.addSet(ae::Statement(money, t));

   // Action to order food from loc2.
   //   Required: we are at loc2 and have money
   //   Outcome:  we have no money and are not hungry
   ae::Action aOrder;
   aOrder.addRequired(ae::Statement(at, loc2));
   aOrder.addRequired(ae::Statement(money, t));
   aOrder.addSet(ae::Statement(money, f));
   aOrder.addSet(ae::Statement(hungry, f));

   return 0;
}
