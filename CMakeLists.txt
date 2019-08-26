cmake_minimum_required(VERSION 3.1)
project(ddg_ex_2_1)
include_directories(src)

set(CMAKE_CXX_FLAGS "-std=c++14")

# OpenVolumeMesh
add_definitions(-DINCLUDE_TEMPLATES)
file(GLOB_RECURSE OpenVolumeMesh_src
  src/OpenVolumeMesh/*.cc
  src/OpenVolumeMesh/*.hh
)
add_library()(OpenVolumeMesh ${OpenVolumeMesh_src})

add_executable (ddg_ex_2_1 src/main.cc)
target_link_libraries(ddg_ex_2_1 OpenVolumeMesh)

