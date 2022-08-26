cmake_minimum_required(VERSION "3.0.0")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")

project(ContainerDriver VERSION 1.0)

add_executable(ContainerDriver main.cpp)

target_include_directories(ContainerDriver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/containers)