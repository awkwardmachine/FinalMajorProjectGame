cmake_minimum_required(VERSION 4.1)
project(3DPlatformer)

set(CMAKE_CXX_STANDARD 20)

add_executable(3DPlatformer src/main.cpp
        src/3DPlatformer.cpp
        src/3DPlatformer.h)

target_link_libraries(3DPlatformer PRIVATE Engine)