cmake_minimum_required(VERSION 4.1)
project(Engine)

set(CMAKE_CXX_STANDARD 20)

# Create a shared library called "Engine" from the listed source files
add_library(Engine SHARED
        src/main.cpp
        src/Platform/Window.cpp
        include/Engine/Platform/Window.h
        include/Engine/Core/DLLExports.h
)

# Specify the include directories for this target.
# PUBLIC means any project that links to Engine will also use this include path
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add a custom command to run after building the Engine library
# POST_BUILD means this runs after Engine is compiled
# The command copies the built library to the 3DPlatformer folder if it's different
add_custom_command(TARGET Engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Engine>           # Path to the built Engine library
        $<TARGET_FILE_DIR:3DPlatformer> # Destination folder
)

# Define a preprocessor macro ENGINE_EXPORTS for the Engine target only
# This is to control DLL export/import symbols on Windows which define what is shared
# in Game Engine through the library
target_compile_definitions(Engine PRIVATE ENGINE_EXPORTS)