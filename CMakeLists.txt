cmake_minimum_required(VERSION 3.5.0)
project(TerrainGen VERSION 0.1.0 LANGUAGES C CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find GLFW
find_package(GLFW3 REQUIRED)
include_directories("/usr/local/include")

# Add Glad
set(GLAD_DIR ${CMAKE_SOURCE_DIR}/include)
include_directories(${GLAD_DIR})
add_library(glad ${CMAKE_SOURCE_DIR}/src/glad.c)

# Set ImGui directories
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)
set(IMGUI_BACKENDS_DIR ${IMGUI_DIR}/backends)

# Add ImGui source files
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_glfw.cpp
    ${IMGUI_BACKENDS_DIR}/imgui_impl_opengl3.cpp
)

# Include ImGui directories
include_directories(${IMGUI_DIR} ${IMGUI_BACKENDS_DIR})

# Create the ImGui library
add_library(imgui ${IMGUI_SOURCES})

# Create the executable
add_executable(TerrainGen src/main.cpp)

# Link libraries (Glad, GLFW, ImGui, OpenGL)
target_link_libraries(TerrainGen glad glfw imgui "-framework OpenGL")
