cmake_minimum_required(VERSION 2.8.9)

include_directories(../lib/googletest)
include_directories(../include)
include_directories(../src)
file(GLOB test_sources "*.cpp")
#Can manually add the sources using the set command as follows:
file(GLOB main_sources "../src/*.cpp")
list(REMOVE_ITEM main_sources "${CMAKE_CURRENT_SOURCE_DIR}/../src/main.cpp")
message("${main_sources}")

add_executable(unitTests ${test_sources} ${main_sources})
target_link_libraries(unitTests gtest_main)
target_link_libraries(unitTests pthread)
target_link_libraries(unitTests X11)
