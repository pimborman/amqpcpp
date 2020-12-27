cmake_minimum_required(VERSION 2.8.12)

project(amqpcpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(
    amqpcpp
    SHARED
    src/AMQP.cpp
    src/AMQPBase.cpp
    src/AMQPException.cpp
    src/AMQPMessage.cpp
    src/AMQPExchange.cpp
    src/AMQPQueue.cpp
    include/AMQPcpp.h
)
target_include_directories(amqpcpp PUBLIC include/)

add_library(
    amqpcpp-static
    STATIC
    src/AMQP.cpp
    src/AMQPBase.cpp
    src/AMQPException.cpp
    src/AMQPMessage.cpp
    src/AMQPExchange.cpp
    src/AMQPQueue.cpp
    include/AMQPcpp.h
)
target_include_directories(amqpcpp-static PUBLIC include/)

#add_subdirectory(rabbitmq-c)
#target_include_directories(rabbitmq PUBLIC rabbitmq-c/librabbitmq/)

target_link_libraries(amqpcpp rabbitmq ssl crypto)
target_link_libraries(amqpcpp-static rabbitmq ssl crypto)

add_executable(example_publish examples/example_publish.cpp)
target_link_libraries(example_publish amqpcpp)

add_executable(example_consume examples/example_consume.cpp)
target_link_libraries(example_consume amqpcpp)

add_executable(example_get examples/example_get.cpp)
target_link_libraries(example_get amqpcpp)
