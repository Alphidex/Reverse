/**
 * @file main.cpp
 * @brief Main entry point for the Reverse Engine
 * @details Initializes OpenGL context, window management, camera system, and main render loop
 */

// // ===== System =====
#include <iostream>
#include <vector>
#include <memory>
#include <filesystem>
#include <glm/glm.hpp>

// // ===== Project =====
#include "header/Camera.h"
#include "header/Light.h"
#include "header/Model.h"
#include "header/Program.h"
#include "header/Config.h"
#include "header/Logger.h"
#include "header/ResourceManager.h"
#include "header/Material.h"
#include "header/Scene.h"
#include "header/Entity.h"
#include "header/MeshRenderer.h"

using std::vector;

// Window parameters
int width = Config::Window::DEFAULT_WIDTH;
int height = Config::Window::DEFAULT_HEIGHT;

float deltaTime = 0.0f;
float lastFrame = 0.0f;


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

// Cube vertex data
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

// Cube faces
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
        
        // Get ResourceManager instance
        ResourceManager& resourceManager = ResourceManager::getInstance();
        
        // Load shaders using ResourceManager
        auto shaderProgram = resourceManager.loadShader(Config::Shaders::DEFAULT_VERTEX, Config::Shaders::DEFAULT_FRAGMENT);
        vector<std::shared_ptr<Shader>> shaderList = {shaderProgram};
        
        // Load textures using ResourceManager (must be after OpenGL context is created)
        auto marbleTexture = resourceManager.loadTexture("./resource/textures/marble.jpg", "diffuse");
        auto wallTexture = resourceManager.loadTexture("./resource/textures/wall.jpg", "diffuse");
        
        // Create Materials with different properties
        auto marbleMaterial = std::make_shared<Material>(shaderProgram);
        marbleMaterial->addTexture(marbleTexture);
        marbleMaterial->setDiffuseColor(glm::vec3(1.0f, 1.0f, 1.0f));
        marbleMaterial->setSpecularColor(glm::vec3(0.8f, 0.8f, 0.8f));
        marbleMaterial->setShininess(64.0f);
        
        auto wallMaterial = std::make_shared<Material>(shaderProgram);
        wallMaterial->addTexture(wallTexture);
        wallMaterial->setDiffuseColor(glm::vec3(0.9f, 0.9f, 0.9f));
        wallMaterial->setSpecularColor(glm::vec3(0.3f, 0.3f, 0.3f));
        wallMaterial->setShininess(32.0f);
        
        // Create meshes with materials
        Mesh cube(cubeVertices, cubeIndices, marbleMaterial);
        Mesh cube2(cubeVertices, cubeIndices, marbleMaterial);
        cube2.setPosition(glm::vec3(2.0f, 0.0f, 0.0f));
        Mesh plane(planeVertices, planeIndices, wallMaterial);

        // ===== NEW: Entity/Component System Demo =====
        // Create a scene to manage entities
        Scene mainScene("MainScene");
        
        // Example: Create entities with MeshRenderer components
        // (Keeping old meshes for now, but showing new system usage)
        
        // Entity 1: A cube using the entity system
        auto cubeEntity = mainScene.createEntity("CubeEntity");
        cubeEntity->getTransform().setPosition(glm::vec3(-2.0f, 1.0f, -2.0f));
        cubeEntity->getTransform().setScale(glm::vec3(0.8f));
        auto cubeMesh = std::make_shared<Mesh>(cubeVertices, cubeIndices, marbleMaterial);
        auto cubeRenderer = cubeEntity->addComponent<MeshRenderer>(cubeMesh, marbleMaterial);
        
        // Entity 2: Another cube with different transform
        auto cube2Entity = mainScene.createEntity("Cube2Entity");
        cube2Entity->getTransform().setPosition(glm::vec3(2.0f, 1.0f, -2.0f));
        cube2Entity->getTransform().setRotation(glm::vec3(0.0f, 45.0f, 0.0f));
        auto cube2Mesh = std::make_shared<Mesh>(cubeVertices, cubeIndices, marbleMaterial);
        auto cube2Renderer = cube2Entity->addComponent<MeshRenderer>(cube2Mesh, marbleMaterial);
        
        LOG_INFO("Scene initialized with " + std::to_string(mainScene.getEntityCount()) + " entities");
        
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
            program.ClearBuffers();

            // Update scene (all entities and their components)
            mainScene.update(deltaTime);

            // Render old meshes (legacy system)
            cube.Draw();
            cube2.Draw();
            plane.Draw();
            
            // Render entities using new system
            for (const auto& entity : mainScene.getEntities()) {
                if (entity->isActive()) {
                    auto renderer = entity->getComponent<MeshRenderer>();
                    if (renderer && renderer->isEnabled()) {
                        renderer->render();
                    }
                }
            }

            // Update camera view-projection matrix
            glfwGetFramebufferSize(window, &width, &height);
            float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
            camera.setPerspective(aspectRatio, Config::Rendering::NEAR_PLANE, Config::Rendering::FAR_PLANE);
            camera.Update(window, deltaTime, shaderList, "cameraView");

            program.SwapBuffers();
        }

        // Log resource statistics before cleanup
        size_t textures, shaders, models;
        resourceManager.getResourceStats(textures, shaders, models);
        LOG_INFO("Resource statistics - Textures: " + std::to_string(textures) + 
                 ", Shaders: " + std::to_string(shaders) + 
                 ", Models: " + std::to_string(models));

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