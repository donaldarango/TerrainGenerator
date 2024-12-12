cmake_minimum_required(VERSION 3.5.0)
project(TerrainGen VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GLFW3 REQUIRED)
include_directories("/usr/local/include")

set(GLAD_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${GLAD_DIR})
add_library(glad ${CMAKE_SOURCE_DIR}/src/glad.c)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)
set(IMGUI_BACKENDS_DIR ${IMGUI_DIR}/backends)

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_glfw.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_opengl3.cpp
)

include_directories(${IMGUI_DIR} ${IMGUI_BACKENDS_DIR})

file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
include_directories(src)

add_library(imgui ${IMGUI_SOURCES})

add_executable(TerrainGen ${SOURCES})

target_link_libraries(TerrainGen glad glfw imgui "-framework OpenGL")
