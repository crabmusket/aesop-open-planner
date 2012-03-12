CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(AesopHeaders
	abstract/AesopTypes.h
		AesopSimpleTypes.h
	abstract/AesopObjects.h
		AesopObjectMap.h
		AesopTypedObjects.h
	abstract/AesopPredicates.h
		AesopSimplePredicates.h
		AesopNamedPredicates.h
		AesopGOAPPredicates.h
	abstract/AesopActionSet.h
		AesopSimpleActionSet.h
	abstract/AesopWorldState.h
		AesopSimpleWorldState.h
		AesopGOAPWorldState.h
	AesopProblem.h
	AesopPlan.h
	abstract/AesopContext.h
		AesopFileWriterContext.h
	AesopReverseAstar.h
)

SET(AesopSources
	abstract/AesopTypes.cpp
	abstract/AesopObjects.cpp
	AesopNamedPredicates.cpp
	AesopGOAPPredicates.cpp
	AesopSimpleActionSet.cpp
	AesopSimpleWorldState.cpp
	AesopGOAPWorldState.cpp
	AesopProblem.cpp
	AesopPlan.cpp
	AesopFileWriterContext.cpp
)

INCLUDE_DIRECTORIES(.)

ADD_LIBRARY(Aesop ${AesopHeaders} ${AesopSources})
