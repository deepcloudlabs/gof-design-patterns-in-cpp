cmake_minimum_required(VERSION 3.16)
project(module07_extension_patterns)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME ON)

set(BOOST_ROOT "D:/DEVEL/stage/opt/boost_1_73_0")
set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}")
set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/stage/lib")
include_directories(${BOOST_INCLUDE_DIRS})

add_executable(decorator decorator/study-decorator.cpp)
target_link_libraries(decorator ${BOOST_LIBRARY_DIRS})

add_executable(iterator1 iterator/iterator1.cpp)
add_executable(iterator2 iterator/iterator2.cpp)

add_executable(visitor1 visitor/visitor1.cpp)
