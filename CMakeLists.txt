cmake_minimum_required(VERSION 3.10)

project(enumerator LANGUAGES CXX VERSION 0.0.1)

add_executable(enumerator enumerator.cpp)
set_property(TARGET enumerator PROPERTY CXX_STANDARD 17)

include(CTest)

add_test(enumerator enumerator)
