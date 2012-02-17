CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(AesopHeaders
	AesopTypes.h
	AesopObjects.h
	AesopPredicates.h
		AesopSimplePredicates.h
		AesopNamedPredicates.h
	AesopActionSet.h
		AesopSimpleActionSet.h
	AesopWorldState.h
		AesopSimpleWorldState.h
	AesopProblem.h
	AesopPlan.h
	AesopContext.h
		AesopFileWriterContext.h
	AesopReverseAstar.h
)

SET(AesopSources
	AesopTypes.cpp
	AesopObjects.cpp
	AesopNamedPredicates.cpp
	AesopSimpleActionSet.cpp
	AesopSimpleWorldState.cpp
	AesopProblem.cpp
	AesopPlan.cpp
	AesopFileWriterContext.cpp
)

INCLUDE_DIRECTORIES(.)

ADD_LIBRARY(Aesop ${AesopHeaders} ${AesopSources})
