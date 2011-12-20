CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(AesopSources
	source/AesopAction.cpp
	source/AesopWorldState.cpp
	source/AesopPlanner.cpp
   source/AesopProblem.cpp
   source/AesopDomain.cpp
)

SET(AesopHeaders
	include/Aesop.h
	include/AesopConfig.h
)

INCLUDE_DIRECTORIES(include)

ADD_LIBRARY(Aesop ${AesopSources} ${AesopHeaders})
