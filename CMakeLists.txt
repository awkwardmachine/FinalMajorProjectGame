cmake_minimum_required(VERSION 4.1)
project(FinalMajorProject)

set(CMAKE_CXX_STANDARD 20)
include(FetchContent) # Enable fetching libraries from github

FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.4)
FetchContent_MakeAvailable(glfw)

add_subdirectory(Engine)
add_subdirectory(3DPlatformer)

target_link_libraries(Engine PRIVATE glfw)

target_include_directories(Engine PUBLIC ${glfw_SOURCE_DIR}/include)
target_include_directories(3DPlatformer PUBLIC ${glfw_SOURCE_DIR}/include)