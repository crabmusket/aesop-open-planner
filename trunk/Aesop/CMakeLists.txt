CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(AesopSources
	AesopTypes.cpp
	AesopObjects.cpp
	AesopPredicates.cpp
	AesopActionSet.cpp
	AesopWorldState.cpp
	AesopProblem.cpp
	AesopPlan.cpp
	AesopContext.cpp
)

SET(AesopHeaders
	AesopTypes.h
	AesopObjects.h
	AesopPredicates.h
	AesopActionSet.h
	AesopWorldState.h
	AesopProblem.h
	AesopPlan.h
	AesopContext.h
	AesopReverseAstar.h
)

INCLUDE_DIRECTORIES(.)

ADD_LIBRARY(Aesop ${AesopSources} ${AesopHeaders})
