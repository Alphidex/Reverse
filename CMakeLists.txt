cmake_minimum_required(VERSION 3.25.1)
project(Reverse)

# Include Directories
include_directories(include)

# Add source
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/glad.c
    src/stb.cpp
    src/Shader.cpp
    src/Optional.cpp
    src/EBO.cpp
    src/VAO.cpp
    src/VBO.cpp
    src/Texture.cpp
    src/Mesh.cpp
    src/Camera.cpp
)

# ImGui sources
set(IMGUI_DIR include/imgui)

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_sources(${PROJECT_NAME} PRIVATE ${IMGUI_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${IMGUI_DIR} ${IMGUI_DIR}/backends)


# Find and link fmt
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL)

