CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(AesopSources
	AesopTypes.cpp
	AesopObjects.cpp
	AesopAction.cpp
	AesopWorldState.cpp
	AesopPlanner.cpp
)

SET(AesopHeaders
	Aesop.h
	AesopRequirements.h
	AesopTypes.h
	AesopObjects.h
	AesopConfig.h
	AesopAction.h
	AesopPlanner.h
	AesopWorldState.h
)

INCLUDE_DIRECTORIES(.)

ADD_LIBRARY(Aesop ${AesopSources} ${AesopHeaders})
