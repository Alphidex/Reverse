/**
 * @file main.cpp
 * @brief Main entry point for the Reverse Engine
 * @details Initializes OpenGL context, window management, camera system, and main render loop
 */

// // ===== System =====
#include <iostream>
#include <vector>
#include <filesystem>
#include <glm/glm.hpp>

// // ===== Project =====
#include "header/Camera.h"
#include "header/Light.h"
#include "header/Model.h"
#include "header/Program.h"
#include "header/Interface.h"
#include "header/Config.h"
#include "header/Logger.h"

using std::vector;

// Window parameters
int width = Config::Window::DEFAULT_WIDTH;
int height = Config::Window::DEFAULT_HEIGHT;

float deltaTime = 0.0f;
float lastFrame = 0.0f;



// Cube mesh data
vector<Vertex> cubeVertices = {
    // Front face (Z+)
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    
    // Back face (Z-)
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
    
    // Left face (X-)
    {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
    {{-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
    
    // Right face (X+)
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
    
    // Top face (Y+)
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
    
    // Bottom face (Y-)
    {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
    {{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}}
};

vector<unsigned int> cubeIndices = {
    // Front face
    0, 1, 2,  2, 3, 0,
    // Back face
    4, 5, 6,  6, 7, 4,
    // Left face
    8, 9, 10,  10, 11, 8,
    // Right face
    12, 13, 14,  14, 15, 12,
    // Top face
    16, 17, 18,  18, 19, 16,
    // Bottom face
    20, 21, 22,  22, 23, 20
};

// Plane mesh data
vector<Vertex> planeVertices = {
    {{-5.0f, -0.5f, -5.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 2.0f}},
    {{ 5.0f, -0.5f, -5.0f}, {0.0f, 1.0f, 0.0f}, {2.0f, 2.0f}},
    {{ 5.0f, -0.5f,  5.0f}, {0.0f, 1.0f, 0.0f}, {2.0f, 0.0f}},
    {{-5.0f, -0.5f,  5.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}
};

vector<unsigned int> planeIndices = {
    0, 1, 2,
    2, 3, 0
};


/// Entry point for the application
/// Initializes OpenGL context, camera, shaders, and main render loop
int main(){
    try {
        // Initialize logging system
        Logger::getInstance().setLogLevel(static_cast<LogLevel>(Config::Logging::DEFAULT_LOG_LEVEL));
        Logger::getInstance().enableFileLogging(Config::Logging::ENABLE_FILE_LOGGING, Config::Logging::LOG_FILE_PATH);
        
        LOG_INFO("======== Reverse Engine Starting ========");
        LOG_INFO("Current working directory: " + std::filesystem::current_path().string());
        
        // Program contains all the GLFW/GLAD config settings and creates window
        Program program(Config::Window::DEFAULT_WIDTH, Config::Window::DEFAULT_HEIGHT);
        GLFWwindow* window = program.GetWindow();
        
        // Shader Setup
        Shader shaderProgram(Config::Shaders::DEFAULT_VERTEX, Config::Shaders::DEFAULT_FRAGMENT);
        Shader interfaceProgram(Config::Shaders::INTERFACE_VERTEX, Config::Shaders::INTERFACE_FRAGMENT);
        vector<Shader> shaderList = {shaderProgram};
        
        /* Interface Setup. Responsible for anything UI related */
        Interface ui(window, interfaceProgram);
        
        // Create textures (must be after OpenGL context is created)
        vector<Texture> cubeTextures = {Texture("./resource/textures/marble.jpg", "diffuse")};
        vector<Texture> planeTextures = {Texture("./resource/textures/wall.jpg", "diffuse")};
        
        Mesh cube(cubeVertices, cubeIndices, cubeTextures);
        Mesh cube2(cubeVertices, cubeIndices, cubeTextures);
        cube2.setPosition(glm::vec3(2.0f, 0.0f, 0.0f));
        Mesh plane(planeVertices, planeIndices, planeTextures);

        
        // Camera
        Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
        glfwSetWindowUserPointer(window, &camera);  // Set camera as user pointer for callbacks
        glfwSetScrollCallback(window, Scroll_Callback);

        // Light configuration
        glm::vec3 lightDir(0.0f, -1.0f, 0.0f);

        while(program.Running())
        {           
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame; // Frame difference in seconds
            lastFrame = currentFrame;

            program.ProcessEvents();

            // Clear buffers with configured background color
            ui.ClearBackgroundColor(
                Config::Rendering::CLEAR_COLOR_R,
                Config::Rendering::CLEAR_COLOR_G,
                Config::Rendering::CLEAR_COLOR_B,
                Config::Rendering::CLEAR_COLOR_A
            );
            program.ClearBuffers();

            // Render scene geometry
            cube.Draw(shaderProgram, "model");
            cube2.Draw(shaderProgram, "model");
            plane.Draw(shaderProgram, "model");

            // Update camera view-projection matrix
            glfwGetFramebufferSize(window, &width, &height);
            float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
            camera.setPerspective(aspectRatio, Config::Rendering::NEAR_PLANE, Config::Rendering::FAR_PLANE);
            camera.Update(window, deltaTime, shaderList, "cameraView");

            program.SwapBuffers();
        }

        // Cleaning Up
        LOG_INFO("Shutting down engine...");
        program.Terminate();
        LOG_INFO("======== Reverse Engine Stopped ========");
        return 0;
    }
    catch (const std::exception& e) {
        LOG_ERROR("Fatal error: " + std::string(e.what()));
        return 1;
    }
}