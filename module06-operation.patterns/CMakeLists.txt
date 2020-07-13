cmake_minimum_required(VERSION 3.16)
project(module06_operation_patterns)

set(CMAKE_CXX_STANDARD 17)

add_executable(command command/study-command.cpp)
add_executable(template-method template-method/template_method.cpp)
add_executable(strategy strategy/strategy1.cpp)
add_executable(state state/state.cpp)
add_executable(handmade-state state/handmade.cpp)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME ON)

set(BOOST_ROOT "D:/DEVEL/stage/opt/boost_1_73_0")
set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}")
set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/stage/lib")
include_directories(${BOOST_INCLUDE_DIRS})
add_executable(msm state/msm.cpp)
target_link_libraries(msm ${BOOST_LIBRARY_DIRS})

add_executable(interpreter interpreter/handmade.cpp)