cmake_minimum_required(VERSION 3.12)

project(MineTestEngine)
set(PROJECT_NAME MineTestEngine)

add_subdirectory(MineTestCore)
add_subdirectory(MineTestEditor)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT MineTestEditor) 
