cmake_minimum_required(VERSION 3.1)
project(ddg_ex_2_1)
INCLUDE_DIRECTORIES(src)

SET(CMAKE_CXX_FLAGS "-std=c++11")

# OpenVolumeMesh
ADD_DEFINITIONS(-DINCLUDE_TEMPLATES)
FILE(GLOB_RECURSE OpenVolumeMesh_src
  src/OpenVolumeMesh/*.cc
  src/OpenVolumeMesh/*.hh
)
ADD_LIBRARY(OpenVolumeMesh ${OpenVolumeMesh_src})

add_executable (ddg_ex_2_1 src/main.cc)
target_link_libraries(ddg_ex_2_1 OpenVolumeMesh)

