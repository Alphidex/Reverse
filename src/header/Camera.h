/**
 * @file Camera.h
 * @brief Camera system for 3D scene navigation
 * @details Provides first-person camera controls with mouse look and keyboard movement
 */

#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/common.hpp>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<vector>
#include<memory>
#include "Shader.h"
#include "Config.h"

/// @brief Stores mouse cursor position
struct MousePosition 
{
    double x, y;
};

/**
 * @brief First-person camera with mouse look and keyboard controls
 * @details Handles view and projection matrices, movement, and rotation
 */
class Camera
{
public:
    /**
     * @brief Constructs a camera at the specified position
     * @param position Initial world position
     */
    Camera(glm::vec3 position);
    
    /**
     * @brief Updates camera state and applies to shaders
     * @param window GLFW window for input handling
     * @param deltaTime Time elapsed since last frame (seconds)
     * @param shaderList List of shared pointers to shaders to update with camera matrix
     * @param uniform Name of the uniform variable in shaders
     */
    void Update(GLFWwindow* window, float deltaTime, std::vector<std::shared_ptr<Shader>>& shaderList, const char* uniform);
    
    /**
     * @brief Sets the perspective projection parameters
     * @param aspectRatio Window width/height ratio
     * @param nearPlane Near clipping plane distance
     * @param farPlane Far clipping plane distance
     */
    void setPerspective(float aspectRatio, float nearPlane, float farPlane);
    
    /**
     * @brief Prints current camera position to console (for debugging)
     */
    void printPosition() const;
    
    /**
     * @brief Gets the current field of view
     * @return Current FOV in degrees
     */
    float getFOV() const { return fov; }
    
    /**
     * @brief Sets the field of view
     * @param newFov New FOV in degrees (clamped to 1-45)
     */
    void setFOV(float newFov);

private:
    // Camera orientation
    glm::vec3 front;              ///< Forward direction vector
    glm::vec3 position;           ///< World position
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); ///< Up direction
    
    // Rotation angles
    float yaw = Config::Camera::DEFAULT_YAW;     ///< Horizontal rotation (degrees)
    float pitch = Config::Camera::DEFAULT_PITCH; ///< Vertical rotation (degrees)
    
    // Mouse handling
    bool firstClick = true;       ///< First right-click detection flag
    MousePosition lastMousePos;   ///< Last recorded mouse position

    // Movement configuration
    float baseMovementSpeed = Config::Camera::BASE_MOVEMENT_SPEED;      ///< Normal movement speed
    float shiftMovementSpeed = Config::Camera::SPRINT_MOVEMENT_SPEED;   ///< Sprint movement speed
    float movementSpeed = baseMovementSpeed; ///< Current active speed
    float mouseSensitivity = Config::Camera::MOUSE_SENSITIVITY;         ///< Mouse rotation sensitivity

    // View and projection
    glm::mat4 cameraView = glm::mat4(1.0f); ///< Combined view-projection matrix
    float aspectRatio = Config::Camera::DEFAULT_ASPECT_RATIO;        ///< Screen aspect ratio
    float farPlane = Config::Camera::DEFAULT_FAR_PLANE;              ///< Far clipping distance
    float nearPlane = Config::Camera::DEFAULT_NEAR_PLANE;            ///< Near clipping distance
    float fov = Config::Camera::DEFAULT_FOV;                         ///< Field of view (degrees)

    /**
     * @brief Handles keyboard input for camera movement
     * @param window GLFW window
     * @param deltaTime Frame time delta
     */
    void KeyboardMovement(GLFWwindow* window, float deltaTime);
    
    /**
     * @brief Handles mouse input for camera rotation
     * @param window GLFW window
     * @param deltaTime Frame time delta
     */
    void MouseMovement(GLFWwindow* window, float deltaTime);
    
    /**
     * @brief Updates a single shader with camera matrix
     * @param shader Shader to update
     * @param uniform Uniform variable name
     */
    void UpdateShader(Shader& shader, const char* uniform);
};

/**
 * @brief GLFW callback for mouse scroll events (zoom)
 * @param window GLFW window
 * @param xoffset Horizontal scroll offset
 * @param yoffset Vertical scroll offset
 */
void Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset);

