cmake_minimum_required(VERSION 3.12)

set(CORE_NAME MineTestCore)

set(ENGINE_PUBLIC_INCLUDES
    includes/MineTestCore/Window.hpp
    includes/MineTestCore/Log.hpp
    includes/MineTestCore/Application.hpp
)
set(ENGINE_PRIVATE_SOURCES
    src/MineTestCore/Window.cpp
    src/MineTestCore/Application.cpp
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