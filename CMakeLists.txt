cmake_minimum_required(VERSION 3.11)
project(rootio LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)
find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})
ROOT_GENERATE_DICTIONARY(event_dict
  event.hpp
  LINKDEF event_linkdef.hpp)
add_library(event OBJECT
  ${CMAKE_CURRENT_BINARY_DIR}/event_dict.cxx
  read.cpp
  write.cpp)
target_include_directories(event PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(event PUBLIC
  ROOT::Core)

add_executable(rio main.cpp)
target_link_libraries(rio PRIVATE
  event
  ROOT::Tree)
