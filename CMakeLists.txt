cmake_minimum_required(VERSION 3.21)
project(project3)

set(CMAKE_CXX_STANDARD 14)

add_executable(project3 main.cpp Recipe.cpp Recipe.h BTree.h)
