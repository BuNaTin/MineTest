cmake_minimum_required(VERSION 3.12)

set(CORE_NAME MineTestCore)

set(ENGINE_PUBLIC_INCLUDES
    includes/MineTestCore/Application.hpp
    includes/MineTestCore/Events.hpp
    includes/MineTestCore/Window.hpp
    includes/MineTestCore/Log.hpp
    includes/MineTestCore/myglad.hpp
    includes/MineTestCore/ResourceManager/ResourceManager.hpp
    includes/MineTestCore/ResourceManager/stb_image.hpp
    includes/MineTestCore/Graphics/Shader.hpp
    includes/MineTestCore/Graphics/Texture.hpp
    includes/MineTestCore/Graphics/PNG.hpp
    includes/MineTestCore/Graphics/Camera.hpp
)
set(ENGINE_PRIVATE_SOURCES
    src/MineTestCore/Window.cpp
    src/MineTestCore/Application.cpp
    src/MineTestCore/Events.cpp
    src/MineTestCore/ResourceManager/ResourceManager.cpp
    src/MineTestCore/Graphics/Shader.cpp
    src/MineTestCore/Graphics/Texture.cpp
    src/MineTestCore/Graphics/Camera.cpp
)
set(ENGINE_PRIVATE_INCLUDES
)

set(ENGINE_ALL_INCLUDES
    ${ENGINE_PUBLIC_INCLUDES}
    ${ENGINE_PRIVATE_INCLUDES}
    ${ENGINE_PRIVATE_SOURCES}
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
