CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(AesopDemoSources
	source/AesopDemo.cpp
	source/AesopDemoActions.cpp
)

SET(AesopDemoHeaders
	include/AesopDemo.h
)

INCLUDE_DIRECTORIES(
	include
	../Aesop/include
)

ADD_EXECUTABLE(AesopDemo ${AesopDemoSources} ${AesopDemoHeaders})

TARGET_LINK_LIBRARIES(AesopDemo Aesop)
