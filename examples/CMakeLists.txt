cmake_minimum_required(VERSION 3.0)
project(rumal-examples)

ADD_EXECUTABLE(ex01 ex01.cpp)
TARGET_LINK_LIBRARIES(ex01 rumal)

ADD_EXECUTABLE(ex02 ex02.cpp)
TARGET_LINK_LIBRARIES(ex02 rumal)
