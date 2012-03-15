CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

FIND_PACKAGE(Threads)

FILE(GLOB_RECURSE gtestHeaders *.h)

INCLUDE_DIRECTORIES(include .)

ADD_LIBRARY(gtest src/gtest-all.cc ${gtestHeaders})

TARGET_LINK_LIBRARIES(gtest ${CMAKE_THREAD_LIBS_INIT})
