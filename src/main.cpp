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
        GLFWwindow* window = program.getWindow();
        
        // Get ResourceManager instance
        ResourceManager& resourceManager = ResourceManager::getInstance();
        
        // Load shaders using ResourceManager
        auto shaderProgram = resourceManager.loadShader(Config::Shaders::DEFAULT_VERTEX, Config::Shaders::DEFAULT_FRAGMENT);
        vector<std::shared_ptr<Shader>> shaderList = {shaderProgram};
        
        // Load textures using ResourceManager
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
        glfwSetScrollCallback(window, scrollCallback);

        // Light configuration
        glm::vec3 lightDir(0.0f, -1.0f, 0.0f);

        while(program.isRunning())
        {           
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame; // Frame difference in seconds
            lastFrame = currentFrame;

            program.processEvents();

            // Clear buffers with configured background color
            program.clearBuffers();

            // Update scene (all entities and their components)
            mainScene.update(deltaTime);
            
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
            camera.update(window, deltaTime, shaderList, "cameraView");

            program.swapBuffers();
        }

        // Log resource statistics before cleanup
        size_t textures, shaders, models;
        resourceManager.getResourceStats(textures, shaders, models);
        LOG_INFO("Resource statistics - Textures: " + std::to_string(textures) + 
                 ", Shaders: " + std::to_string(shaders) + 
                 ", Models: " + std::to_string(models));

        // Cleaning Up
        LOG_INFO("Shutting down engine...");
        program.terminate();
        LOG_INFO("======== Reverse Engine Stopped ========");
        return 0;
    }
    catch (const std::exception& e) {
        LOG_ERROR("Fatal error: " + std::string(e.what()));
        return 1;
    }
}