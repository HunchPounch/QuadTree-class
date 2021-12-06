cmake_minimum_required(VERSION 2.8)

project(N2)

set(N2_src test.cpp QuadTree.cpp main.cpp CArray.cpp functions.cpp)
set(N2_hdr QuadTree.h test.h Header.h CArray.h)

add_executable(${PROJECT_NAME} ${N2_src} ${N2_hdr})