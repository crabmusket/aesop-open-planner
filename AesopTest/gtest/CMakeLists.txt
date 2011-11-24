CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

FILE(GLOB_RECURSE gtestHeaders *.h)

INCLUDE_DIRECTORIES(include .)

ADD_LIBRARY(gtest src/gtest-all.cc ${gtestHeaders})
