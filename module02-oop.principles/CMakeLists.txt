cmake_minimum_required(VERSION 3.16)
project(module02_oop_principles)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME ON)

set(BOOST_ROOT "D:/DEVEL/stage/opt/boost_1_73_0")
set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}")
set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/stage/lib")
include_directories(${BOOST_INCLUDE_DIRS})

add_executable(SRP SRP.cpp)
target_link_libraries(SRP ${BOOST_LIBRARY_DIRS})

add_executable(OCP OCP.cpp)
add_executable(LSP LSP.cpp)
add_executable(ISP ISP.cpp)
add_executable(DIP DIP.cpp)