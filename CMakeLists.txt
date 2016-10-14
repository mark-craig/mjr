cmake_minimum_required(VERSION 2.8.9)
project(mjr)
option(test "option to build the test cases" OFF)

#Bring the headers, such as Student.h into the project
include_directories(include)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/main.cpp)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

add_executable(mjr ${SOURCES})

TARGET_LINK_LIBRARIES(mjr pthread)
TARGET_LINK_LIBRARIES(mjr X11)

# testing
if(test)
  add_subdirectory(lib/googletest)
  add_subdirectory(test)
endif(test)