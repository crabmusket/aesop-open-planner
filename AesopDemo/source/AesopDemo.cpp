//
//

#include <stdio.h>

#include "AesopDemo.h"
#include "Aesop.h"

int main(int argc, char **argv)
{
   // Create several predicate names and values.
   ae::PName pred1 = "Pred1";
   ae::PName pred2 = "Pred2";
   ae::PName pred3 = "Pred3";
   ae::PVal val1 = 3;
   ae::PVal val2 = 4;
   ae::PVal val3 = 'u';

   // Create a WorldState, set pred1 to 3 and initialise pred2 as unset.
   ae::WorldState ws1;
   ws1.setPredicate(pred1, val1);
   ws1.unsetPredicate(pred2);

   // Create another WorldState copied from the first and make some changes.
   ae::WorldState ws2 = ws1;
   ws2.setPredicate(pred1, val2);
   ws2.setPredicate(pred3, val3);

   // Print out the number of differences between ws1 and ws2.
   printf("Comparison of ws1 and ws2: %d\n", ae::WorldState::comp(ws1, ws2));
   // Should have printed 1, since ws1 and ws2 differ only once, in the value
   // of pred1. (Predicates not set in both states are not counted.)

   return 0;
}
