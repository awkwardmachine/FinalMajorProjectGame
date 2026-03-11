cmake_minimum_required(VERSION 4.1)
project(Engine)

set(CMAKE_CXX_STANDARD 20)

set(STB_IMPL_SRC ${CMAKE_BINARY_DIR}/stb_impl.cpp)
if (NOT EXISTS ${STB_IMPL_SRC})
    file(WRITE ${STB_IMPL_SRC}
            "#define STB_IMAGE_IMPLEMENTATION\n#include \"stb/stb_image.h\"\n")
endif ()

# Create a shared library called "Engine" from the listed source files
add_library(Engine SHARED
        ${STB_IMPL_SRC}

        src/main.cpp
        src/Platform/Window.cpp
        include/Engine/Platform/Window.h
        include/Engine/Core/DLLExports.h
        include/Engine/Core/Logger.h
        include/Engine/Core/EngineInit.h
        src/Core/EngineInit.cpp
        src/Core/Logger.cpp
        include/Engine/Core/Application.h
        include/Engine/Core/Game.h
        src/Core/Game.cpp
        src/Core/Application.cpp
        include/Engine/Core/EntryPoint.h
        include/Engine/Renderer/Api/RendererFactory.h
        src/Renderer/Api/RendererFactory.cpp

        ${CMAKE_SOURCE_DIR}/External/glad/src/glad.c
        include/Engine/Renderer/Api/Renderer.h
        include/Engine/Renderer/Api/OpenGLRenderer.h
        src/Renderer/Api/OpenGLRenderer.cpp
        include/Engine/Renderer/Buffers/VertexArray.h
        src/Renderer/Buffers/VertexArray.cpp
        include/Engine/Renderer/Buffers/VertexBuffer.h
        src/Renderer/Buffers/VertexBuffer.cpp
        include/Engine/Renderer/Buffers/IndexBuffer.h
        src/Renderer/Buffers/IndexBuffer.cpp
        include/Engine/Renderer/Resources/Shader.h
        src/Renderer/Resources/Shader.cpp
        include/Engine/Renderer/Resources/Texture.h
        src/Renderer/Resources/Texture.cpp
        src/Utils/FileUtils.cpp
)

# Link glfw and glm. glm is PUBLIC so its headers are available to
# targets that link against Engine (e.g. 3DPlatformer).
target_link_libraries(Engine PRIVATE glfw PUBLIC glm)

# Specify the include directories for this target.
target_include_directories(Engine PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/External/glad/include
        ${CMAKE_SOURCE_DIR}/External
        ${glm_SOURCE_DIR}
)


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
