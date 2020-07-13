cmake_minimum_required(VERSION 3.16)
project(module05_construction_patterns)

set(CMAKE_CXX_STANDARD 17)

add_executable(composite-person builder/composite-person.cpp builder/Person.h builder/Person.cpp builder/PersonAddressBuilder.h builder/PersonJobBuilder.h builder/PersonBuilder.h builder/PersonBuilder.cpp)
add_executable(point factory-method/point.cpp)
add_executable(inner-factory abstract-factory/InnerFactory.cpp)
add_executable(factory-exercise abstract-factory/FactoryExercise.cpp)
add_executable(factory abstract-factory/Factory.cpp)
add_executable(abstract-factory abstract-factory/AbstractFactory.cpp)
add_executable(memento memento/memento.cpp)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME ON)

set(BOOST_ROOT "D:/DEVEL/stage/opt/boost_1_73_0")
set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}")
set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/stage/lib")
include_directories(${BOOST_INCLUDE_DIRS})
add_executable(prototype prototype/Prototype.cpp)
target_link_libraries(prototype ${BOOST_LIBRARY_DIRS})
