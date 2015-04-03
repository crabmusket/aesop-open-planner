# Aesop Open Planner #



Aesop is a C++ library that implements STRIPS-like automatic planning. It is targeted at video game character AI but is designed to be generally applicable to automated planning problems. Its name, Aesop, is a weak acronym that stands for Action-Entry Sequencing Open Planner.

See GettingStarted for brief instructions on using Aesop in your own project. I try to maintain up-to-date Doxygen output [here](http://www.ug.it.usyd.edu.au/~dbuc6168/public/aesopdoc/).

## Features ##

  * Easy interface to define actions and world states.
  * Action costs and preferences are used to find the plan of least resistance.
  * Immediate and time-sliced planning.

## What is automatic planning? ##

Traditional game AI requires that designers and programmers work together to create state machines, behaviour trees, or scripted activity for non-player characters. These methods explicitly define an NPC's behaviour in certain situations. But when an AI-controlled character finds itself in circumstances that the designers didn't forsee, it's in trouble.

Planning AI takes a different approach. Instead of defining a character's actions in each situation, a planner stores knowledge about the different actions an NPC can do, and what their expected effects on the world should be. Given this information, the planner can create a sequence of actions on-the-fly to deal with any particular world state given to it.

There are numerous advantages to this approach:
  * **Separation of design and internals:** designers choose action sets, coders implement actions.
  * **Code reuse:** actions and action sets can apply to multiple character types.
  * **Graceful failure:** characters in unexpected situations still come up with reasonable plans.
  * **Procedural AI:** the work of coming up with a logical plan is offloaded to the planner, freeing designers and coders for more important tasks.

For more information on planning, check out:

  * [GOAP](http://web.media.mit.edu/~jorkin/goap.html) by Jeff Orkin, whose work heavily inspired this project.
  * [STRIPS](http://en.wikipedia.org/wiki/STRIPS), a planning language developed at Stanford
  * [PDDL](http://en.wikipedia.org/wiki/Planning_Domain_Definition_Language), a planning language

## Project status ##

As of August 2012, this project is on hold, and any version of the code obtained is considered pre-alpha software. **At the moment, the most recent code can be found in /branches/goap2 instead of /trunk.**

## Acknowledgements ##

Aesop makes use of the following popular open-source software:

  * [googletest](http://code.google.com/p/googletest/)
  * [CMake](http://www.cmake.org)
  * [Doxygen](http://www.doxygen.org)
  * [TortoiseSVN](http://tortoisesvn.net)

Without the hard work put into these codebases by some very talented people, developing my own project would have been a lot more difficult!

## Resources ##

If you're looking for other game-AI related information or resources, check these out:

  * [Recast](http://code.google.com/p/recastnavigation) Automatic navmesh generation and pathfinding.
  * [OpenSteer](http://opensteer.sourceforge.net/) Flocking and steering behaviour for crowds.
  * [AIGameDev](http://aigamedev.com) News, articles and tutorials on game AI.