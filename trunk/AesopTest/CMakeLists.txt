CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(AesopTestSources
	source/AesopTest.cpp
)

SET(AesopTestHeaders
	include/AesopTest.h
	include/AesopActionTest.h
	include/AesopWorldStateTest.h
	include/AesopPlannerTest.h
)

INCLUDE_DIRECTORIES(
	include
	../Aesop/include
	./gtest/include
)

ADD_SUBDIRECTORY(gtest)

ADD_EXECUTABLE(AesopTest ${AesopTestSources} ${AesopTestHeaders})

TARGET_LINK_LIBRARIES(AesopTest Aesop gtest)
