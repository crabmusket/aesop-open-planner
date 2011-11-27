///
/// @class Planner
/// Note that careful use of the finaliseSlicedPlan() method enables a plan to
/// be 'queued' while another plan is being stored.
/// @code
///    // Create some plan.
///    planner.setStart(&start);
///    planner.setGoal(&goal);
///    planner.plan(&context);
///    // Setup a new planning space.
///    planner.setStart(&newStart);
///    planner.setGoal(&newGoal);
///    // Calculate the plan, but do not finalise it.
///    planner.initSlicedPlan(&context);
///    while(planner.isPlanning())
///       updateSlicedPlan(context);
/// @endcode
/// Now, upon the next call to finaliseSlicedPlan(), the current plan will
/// be replaced by the already-completed new one. The planning loop could be
/// spread out over multiple loops of an application, while an agent enacts
/// the first plan, for example.
///
