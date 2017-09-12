cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(coc_coc_number_pronunciation)

include_directories(.)

file(GLOB SOURCES "*.cpp")

add_definitions(-std=c++0x)

add_executable(coc_coc_number_pronunciation ${SOURCES})
