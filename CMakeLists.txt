cmake_minimum_required(VERSION 3.0)

project(rumal)

add_executable(rumal main.cpp)

install(TARGETS rumal RUNTIME DESTINATION bin)
