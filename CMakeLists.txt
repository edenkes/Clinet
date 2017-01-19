cmake_minimum_required(VERSION 3.6)
project(Client)
message(STATUS "start running cmake...")
find_package(Boost 1.57.0 COMPONENTS system filesystem thread REQUIRED)
if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    include/connectionHandler.h
    src/connectionHandler.cpp
        src/BidiMessegeEncoderDecoder.cpp include/BidiMessegeEncoderDecoder.h src/keyboardInput.cpp include/keyboardInput.h src/serverInput.cpp include/serverInput.h src/bidiClient.cpp)

add_executable(Client ${SOURCE_FILES})
if(Boost_FOUND)
target_link_libraries(Client ${Boost_LIBRARIES})
endif()

