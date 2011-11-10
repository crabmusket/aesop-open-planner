//
//

#include <stdio.h>

#include "AesopDemo.h"
#include "Aesop.h"

int main(int argc, char **argv)
{
   // Create several predicate names.
   ae::PName pred1("Pred1");
   ae::PName pred2("Pred2");
   ae::PName pred3("Pred3");

   // Create a WorldState, set pred1 to 3 and initialise pred2 as unset.
   ae::WorldState ws1;
   ws1.setPredicate(pred1, 3);
   ws1.unsetPredicate(pred2);

   // Create another WorldState copied from the first and make some changes.
   ae::WorldState ws2 = ws1;
   ws2.setPredicate(pred1, 4);
   ws2.setPredicate(pred3, 'u');

   // Print out the number of differences between ws1 and ws2.
   printf("Comparison of ws1 and ws2: %d\n", ae::WorldState::comp(ws1, ws2));

   return 0;
}
