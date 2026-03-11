cmake_minimum_required(VERSION 4.1)
project(3DPlatformer)

set(CMAKE_CXX_STANDARD 20)

add_executable(3DPlatformer src/main.cpp
        src/3DPlatformer.cpp
        src/3DPlatformer.h)

target_link_libraries(3DPlatformer PRIVATE Engine)

# Copy shaders and textures next to the executable so relative paths resolve at runtime
add_custom_command(TARGET 3DPlatformer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:3DPlatformer>/shaders
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/textures
        $<TARGET_FILE_DIR:3DPlatformer>/textures
)
