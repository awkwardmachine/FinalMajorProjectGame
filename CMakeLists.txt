cmake_minimum_required(VERSION 4.1)
project(FinalMajorProject)

set(CMAKE_CXX_STANDARD 20)
include(FetchContent) # Enable fetching libraries from github

FetchContent_Declare(glfw GIT_REPOSITORY https://github.com/glfw/glfw.git GIT_TAG 3.4)
FetchContent_Declare(glm GIT_REPOSITORY https://github.com/g-truc/glm.git GIT_TAG 1.0.3)
FetchContent_MakeAvailable(glfw glm)

add_subdirectory(Engine)
add_subdirectory(3DPlatformer)

if (WIN32)
    target_link_libraries(Engine PUBLIC opengl32)
elseif (APPLE)
    find_library(OpenGL_LIBRARY OpenGL REQUIRED)
    target_link_libraries(Engine PUBLIC ${OpenGL_LIBRARY})
else ()
    target_link_libraries(Engine PUBLIC GL)
endif ()

target_include_directories(Engine PUBLIC ${glfw_SOURCE_DIR}/include)
target_include_directories(3DPlatformer PUBLIC ${glfw_SOURCE_DIR}/include)