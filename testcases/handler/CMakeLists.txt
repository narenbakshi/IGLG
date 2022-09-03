cmake_minimum_required(VERSION 3.17)
 
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)



# Locate GTest
project(testcases)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests test.cpp /home/job2/thesis_backup/factory/handlerFactory.c /home/job2/thesis_backup/nanoMsg/nano_pubsub.c /home/job2/thesis_backup/zeroMq/zeromq_pubsub.c /home/job2/thesis_backup/pahomqtt/pahomq_pubsub.c)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread  nanomsg zmq czmq paho-mqtt3a)

set (CMAKE_CXX_FLAGS "-w")
include_directories("/home/job2/thesis_backup/utils")
link_directories("/home/job2/thesis_backup/utils")
include_directories("/usr/include/libxml2")
link_directories("/usr/include/libxml2")
