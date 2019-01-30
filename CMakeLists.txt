cmake_minimum_required(VERSION 3.1)
project(CubeSolver)

find_library(PTHREAD pthread)
find_package(Boost COMPONENTS REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

set(CMAKE_GENERATOR_PLATFORM x64)
set(CMAKE_CXX_FLAGS "-Ofast -m64 -mcmodel=medium -march=x86-64")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_executable(main solver.cpp test.cpp ui.cpp)
target_link_libraries(main ${PTHREAD} ${Boost_LIBRARIES})