///
/// @mainpage
///
/// <p>Aesop is a C++ library that implements STRIPS-like automatic planning. It
/// is targeted at video game character AI but is designed to be generally
/// applicable to automated planning problems. Its name, Aesop, is a weak
/// acronym that stands for Action-Entry Sequencing Open Planner.</p>
///
/// <h2>Features</h2>
///
/// <ul>
///    <li>Easy interface to define actions and world states.</li>
///    <li>Action costs and preferences are used to find the plan of least
///        resistance.</li>
///    <li>Immediate and time-sliced planning.</li>
/// </ul>
///
/// <h2>What is automatic planning?</h2>
///
/// <p>Traditional game AI requires that designers and programmers work together
/// to create state machines, behaviour trees, or scripted activity for non-
/// player characters. These methods explicitly define an NPC's behaviour in
/// certain situations. But when an AI-controlled character finds itself in
/// circumstances that the designers didn't forsee, it's in trouble.</p>
///
/// <p>Planning AI takes a different approach. Instead of defining a character's
/// actions in each situation, a planner stores knowledge about the different
/// actions an NPC can do, and what their expected effects on the world should
/// be. Given this information, the planner can create a sequence of actions
/// on-the-fly to deal with any particular world state given to it.</p>
///
/// <p>There are numerous advantages to this approach:</p>
/// <ul>
///    <li><b>Separation of design and internals:</b> designers choose action
///        sets, coders implement actions.</li>
///    <li><b>Code reuse:</b> actions and action sets can apply to multiple
///        character types.</li>
///    <li><b>Graceful failure:</b> characters in unexpected situations still
///        come up with reasonable plans.</li>
///    <li><b>Procedural AI:</b> the work of coming up with a logical plan is
///        offloaded to the planner, freeing designers and coders for more
///        important tasks.</li>
/// </ul>
///
/// <p>For more information on planning, check out:</p>
/// <ul>
///    <li><a href="http://web.media.mit.edu/~jorkin/goap.html">GOAP</a> by
///        Jeff Orkin, whose work heavily inspired this project.</li>
///    <li><a href="http://en.wikipedia.org/wiki/STRIPS">STRIPS</a></li>
///    <li><a href="http://en.wikipedia.org/wiki/Planning_Domain_Definition_Language">
///        PDDL</a></li>
/// </ul>
///
/// <h2>Acknowledgements</h2>
///
/// <p>Aesop makes use of the following popular open-source software:</p>
/// <ul>
///    <li><a href="http://code.google.com/p/googletest/">googletest</a></li>
///    <li><a href="http://www.cmake.org">CMake</a></li>
///    <li><a href="http://www.doxygen.org">Doxygen</a></li>
/// </ul>
/// <p>Without the hard work put into these codebases by some very talented people,
/// developing my own project would have been a lot more difficult!</p>
///
