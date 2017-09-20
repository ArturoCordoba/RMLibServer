cmake_minimum_required(VERSION 3.8)
project(RMLibServer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp DataStructures/Node.cpp DataStructures/Node.h DataStructures/LinkedList.cpp DataStructures/LinkedList.h DataStructures/RMRef_H.cpp DataStructures/RMRef_H.h Socket/SocketServer.cpp Socket/SocketServer.h)
add_executable(RMLibServer ${SOURCE_FILES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
