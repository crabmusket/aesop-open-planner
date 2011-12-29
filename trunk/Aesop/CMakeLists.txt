CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(AesopSources
	source/AesopAction.cpp
	source/AesopWorldState.cpp
	source/AesopPlanner.cpp
)

SET(AesopHeaders
	include/Aesop.h
	include/AesopConfig.h
	include/AesopAction.h
	include/AesopPlanner.h
	include/AesopWorldState.h
)

INCLUDE_DIRECTORIES(include)

ADD_LIBRARY(Aesop ${AesopSources} ${AesopHeaders})
