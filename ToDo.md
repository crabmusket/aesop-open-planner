# Roadmap #

  * **_Pre-alpha_**:
    * Not yet at alpha status.
  * _Alpha_:
    * Support single-parameter predicates and world states
    * Include regressive and progressive A`*` algorithms
  * _Beta_:
    * Demo, hopefully interactive
    * Some form of benchmarking?
    * Complete unit tests
  * _Release_:
    * PDDL module
    * Bug-free and stable as possible

# To Do #

  * Parse PDDL files
    * Use STRIPS subset like [this](http://eecs.oregonstate.edu/ipc-learn/documents/strips-pddl-subset.pdf) or [this](http://users.cecs.anu.edu.au/~patrik/pddlman/writing.html)
      * Support requirements `strips`, `equality`, and maybe `typing`
    * Implement in separate project from demo as standalone library
    * Borrow flex/bison files from [VAL](http://planning.cis.strath.ac.uk/VAL/)?
  * Benchmarking app
    * Separate from demo?
    * Possible: generate random planning problems? [Like so](http://www.loria.fr/~hoffmanj/ff-domains.html)
    * Plans-per-second metric?
    * Threaded?
  * Predicates
    * Support flexible user-defined predicates
      * Support logical expressions in effects and preconditions
    * Retain basic, high-performance ones as well
  * Constraints
    * Conditions that are checked against each possible world state during search