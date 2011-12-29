CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(AesopDemoSources
	AesopDemo.cpp
	AesopDemoActions.cpp
)

SET(AesopDemoHeaders
	AesopDemo.h
)

INCLUDE_DIRECTORIES(
	include
	../Aesop
)

ADD_EXECUTABLE(AesopDemo ${AesopDemoSources} ${AesopDemoHeaders})

TARGET_LINK_LIBRARIES(AesopDemo Aesop)
