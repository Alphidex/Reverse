cmake_minimum_required(VERSION 4.1.0)
project(Reverse)

# Dynamic Linking
set(VCPKG_TARGET_TRIPLET "x64-mingw-static")
set(CMAKE_TOOLCHAIN_FILE "C:/Programs - Main/vcpkg/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_PREFIX_PATH "C:/Programs - Main/vcpkg/installed/x64-mingw-static")

# # Include Directories
include_directories(include)

# Add source
add_executable(${PROJECT_NAME} main.cpp glad.c)

# Find and link fmt
find_package(fmt REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL fmt::fmt)

