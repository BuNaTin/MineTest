cmake_minimum_required(VERSION 3.12)

set(CORE_NAME MineTestCore)

set(ENGINE_PUBLIC_INCLUDES
    includes/MineTestCore/System/Application.hpp
    includes/MineTestCore/System/Events.hpp
    includes/MineTestCore/System/Window.hpp
    includes/MineTestCore/System/Log.hpp
    includes/MineTestCore/GameLogic/Inventory.hpp
    includes/MineTestCore/GameLogic/Gamelogic.hpp
    includes/MineTestCore/Input/Commands.hpp
    includes/MineTestCore/Input/InputHandler.hpp
    includes/MineTestCore/ResourceManager/ResourceManager.hpp
    includes/MineTestCore/ResourceManager/stb_image.hpp
    includes/MineTestCore/Graphics/myglad.hpp
    includes/MineTestCore/Graphics/Shader.hpp
    includes/MineTestCore/Graphics/Texture.hpp
    includes/MineTestCore/Graphics/PNG.hpp
    includes/MineTestCore/Graphics/Camera.hpp
    includes/MineTestCore/Graphics/Mesh.hpp
    includes/MineTestCore/Graphics/VoxelRenderer.hpp
    includes/MineTestCore/Graphics/LineBatch.hpp
    includes/MineTestCore/Voxels/Voxel.hpp
    includes/MineTestCore/Voxels/Chunk.hpp
    includes/MineTestCore/Voxels/Chunks.hpp
    includes/MineTestCore/Lighting/Lightmap.hpp
    includes/MineTestCore/Lighting/LightSolver.hpp
)
set(ENGINE_PRIVATE_SOURCES
    src/MineTestCore/System/Window.cpp
    src/MineTestCore/System/Application.cpp
    src/MineTestCore/System/Events.cpp
    src/MineTestCore/GameLogic/Inventory.cpp
    src/MineTestCore/GameLogic/Gamelogic.cpp
    src/MineTestCore/Input/Commands.cpp
    src/MineTestCore/Input/InputHandler.cpp
    src/MineTestCore/ResourceManager/ResourceManager.cpp
    src/MineTestCore/Graphics/Shader.cpp
    src/MineTestCore/Graphics/Texture.cpp
    src/MineTestCore/Graphics/Camera.cpp
    src/MineTestCore/Graphics/Mesh.cpp
    src/MineTestCore/Graphics/VoxelRenderer.cpp
    src/MineTestCore/Graphics/LineBatch.cpp
    src/MineTestCore/Voxels/Chunk.cpp
    src/MineTestCore/Voxels/Chunks.cpp
    src/MineTestCore/Lighting/Lightmap.cpp
    src/MineTestCore/Lighting/LightSolver.cpp
)
set(ENGINE_PRIVATE_INCLUDES
)

set(ENGINE_ALL_INCLUDES
    ${ENGINE_PUBLIC_INCLUDES}
    ${ENGINE_PRIVATE_INCLUDES}
    ${ENGINE_PRIVATE_SOURCES}
) 

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES 
    ${ENGINE_ALL_INCLUDES}
)

add_library(${CORE_NAME} 
    STATIC 
        ${ENGINE_ALL_INCLUDES}
)

target_include_directories(${CORE_NAME}  
    PUBLIC 
        includes
)

target_include_directories(${CORE_NAME}  
    PRIVATE 
        src
)

add_subdirectory(
    ../external/glfw
    ${CMAKE_CURRENT_BINARY_DIR}/glfw
)
target_link_libraries(${CORE_NAME} PRIVATE glfw)

add_subdirectory(
    ../external/spdlog
    ${CMAKE_CURRENT_BINARY_DIR}/spdlog
)
target_link_libraries(${CORE_NAME} PRIVATE spdlog)

add_subdirectory(
    ../external/glad
    ${CMAKE_CURRENT_BINARY_DIR}/glad
)
target_link_libraries(${CORE_NAME} PRIVATE glad)

add_subdirectory(
    ../external/glm
    ${CMAKE_CURRENT_BINARY_DIR}/glm
)
target_link_libraries(${CORE_NAME} PRIVATE glm)
