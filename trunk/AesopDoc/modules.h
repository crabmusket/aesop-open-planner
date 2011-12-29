///
/// @defgroup Aesop Aesop
/// @brief Aesop planning library.
///
/// <p>This module contains the Aesop planning library, all you need to add
/// automated planning to your own project.</p>
///
/// <p>To create a domain, problem and plan using Aesop, you'll need to do
/// the following. I recommend that these steps be performed in the order
/// they're given, to prevent odd behaviour. If you know what you're doing,
/// there's nothing to stop you adding requirements to a Domain mid-plan...
/// but if you're doing that it's likely not what you intended.</p>
/// <ol>
///    <li>Create an ae::Domain, optionally passing it a name to uniquely
///        identify it. A Domain is the representation of a problem space;
///        it describes a particular class of problem, as we'll see below:
///        <ol>
///            <li>Call ae::Domain::addRequirement to define the requirements
///                of the Domain. The requirements specify the features
///                your Domain can support, and will affect its performance.</li>
///            <li>Use ae::Domain::addType to define the object types that
///                exist in the problem Domain. The types of a Domain are
///                a hierarchy, where all types are children of "object".</li>
///            <li>ae::Domain::addPredicate can then be called to define
///                the Domain's predicates. Predicates are the properties
///                that describe the world state. For example, to define the
///                <i>in</i> predicate for an "object" and a "container"
///                allows the Domain to express the idea that some object
///                is inside some other object, which must be a type of
///                container.</li>
///            <li>Finally, ae::Domain::addAction is used to add Actions
///                that are used to solve problems within the Domain. For
///                more information on Actions, @see ae::Action.</li>
///        </ol>
///    </li>
///    <li></li>
///    <li></li>
///    <li></li>
///    <li></li>
/// </ol>
///

///
/// @defgroup AesopDemo AesopDemo
/// @brief Aesop demo application.
///
/// AesopDemo is a small example application that provides a practical
/// implementation of Aesop's features. It is primarily used as a testbed for
/// deleopment, until a full suite of unit tests is available, as well as a
/// proof of functionality.
///

///
/// @defgroup AesopTest AesopTest
/// @brief Aesop testing suite.
///
/// This module contains a suite of unit tests written with googletest. They
/// are used when developing, to make sure that modifications to the Aesop
/// classes do not break its intended functionality. If you don't plan on
/// modifying any of the source code in the Aesop module, then you shouldn't
/// need to worry about any of this code.
///
