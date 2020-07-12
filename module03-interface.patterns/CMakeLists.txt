cmake_minimum_required(VERSION 3.16)
project(module03_interface_patterns)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME ON)

set(BOOST_ROOT "D:/DEVEL/stage/opt/boost_1_73_0")
set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}")
set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/stage/lib")
include_directories(${BOOST_INCLUDE_DIRS})

add_executable(adapter.pattern adapter/adapter.pattern.cpp)
add_executable(adapter.pattern.with.caching adapter/adapter.pattern.with.caching.cpp)
target_link_libraries(adapter.pattern.with.caching ${BOOST_LIBRARY_DIRS})
add_executable(facade-example facade/trading-api.cpp)
add_executable(composite-example2 composite/deep-learning.cpp)
add_executable(bridge-example bridge/graphics.cpp)
