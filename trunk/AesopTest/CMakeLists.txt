CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(AesopTestSources
	AesopTest.cpp
)

SET(AesopTestHeaders
	AesopTest.h
	tests/AesopActionSetTest.h
	tests/AesopWorldStateTest.h
	tests/AesopPlannerTest.h
	tests/AesopTypesTest.h
	tests/AesopObjectsTest.h
	tests/AesopSimpleWorldStateTest.h
)

INCLUDE_DIRECTORIES(
	../Aesop
	./gtest/include
)

ADD_SUBDIRECTORY(gtest)

ADD_EXECUTABLE(AesopTest ${AesopTestSources} ${AesopTestHeaders})

TARGET_LINK_LIBRARIES(AesopTest Aesop gtest)
