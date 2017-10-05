cmake_minimum_required(VERSION 3.8)
project(RMLibServer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp DataStructures/Node.cpp DataStructures/Node.h DataStructures/LinkedList.cpp DataStructures/LinkedList.h DataStructures/RMRef_H.cpp DataStructures/RMRef_H.h Socket/SocketServer.cpp Socket/SocketServer.h MemoryManager.cpp MemoryManager.h Socket/SocketClient.cpp Socket/SocketClient.h Servers/ActiveServer.cpp Servers/ActiveServer.h Servers/PasiveServer.cpp Servers/PasiveServer.h Servers/Server.cpp Servers/Server.h)
add_executable(RMLibServer ${SOURCE_FILES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
