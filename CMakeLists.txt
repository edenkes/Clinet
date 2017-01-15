cmake_minimum_required(VERSION 3.6)
project(Client)

find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    include/connectionHandler.h
    src/connectionHandler.cpp
    src/echoClient.cpp src/BidiMessegeEncoderDecoder.cpp include/BidiMessegeEncoderDecoder.h src/Packet.cpp include/Packet.h src/encoderDecoderTester.cpp)

add_executable(Client ${SOURCE_FILES})
target_link_libraries(Client ${Boost_LIBRARIES})


