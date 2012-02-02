CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(AesopSources
	AesopTypes.cpp
	AesopObjects.cpp
	AesopPredicates.cpp
	AesopActionSet.cpp
	AesopWorldState.cpp
)

SET(AesopHeaders
	Aesop.h
	AesopTypes.h
	AesopObjects.h
	AesopPredicates.h
	AesopConfig.h
	AesopActionSet.h
	AesopWorldState.h
)

INCLUDE_DIRECTORIES(.)

ADD_LIBRARY(Aesop ${AesopSources} ${AesopHeaders})
