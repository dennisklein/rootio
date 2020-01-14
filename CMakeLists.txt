cmake_minimum_required(VERSION 3.5)
project(rootio LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)
find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})

include_directories(${CMAKE_SOURCE_DIR})
ROOT_GENERATE_DICTIONARY(G__event
  event.hpp
  LINKDEF event_linkdef.hpp)
add_library(event SHARED
  G__event.cxx)
target_include_directories(event PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(event PUBLIC
  ROOT::Core ROOT::Tree ROOT::RIO)

add_executable(rio main.cpp)
target_link_libraries(rio PRIVATE
  event)
