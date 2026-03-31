/**
 * @file Camera.cpp
 * @brief Implementation of the Camera system
 */

#include <iostream>
#include "header/Camera.h"
#include "header/Config.h"
#include "header/Logger.h"

Camera::Camera(glm::vec3 position) : position(position) {}

void Camera::keyboardMovement(GLFWwindow* window, float deltaTime)
{
    float calibratedMovementSpeed = deltaTime * movementSpeed;

    // Movement
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += front * calibratedMovementSpeed;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= front * calibratedMovementSpeed;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += glm::normalize(glm::cross(front, up)) * calibratedMovementSpeed;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= glm::normalize(glm::cross(front, up)) * calibratedMovementSpeed;
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        position += up * calibratedMovementSpeed;
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        position -= up * calibratedMovementSpeed;
    // Shifting
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        movementSpeed = shiftMovementSpeed;
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        movementSpeed = baseMovementSpeed;
}

void Camera::printPosition() const {
    if (Config::Debug::PRINT_CAMERA_POSITION) {
        LOG_DEBUG("Camera Position: (" + 
                  std::to_string(position.x) + ", " + 
                  std::to_string(position.y) + ", " + 
                  std::to_string(position.z) + ")");
    }
}

void Camera::setFov(float newFov) {
    fov = glm::clamp(newFov, Config::Camera::MIN_FOV, Config::Camera::MAX_FOV);
}

void Camera::mouseMovement(GLFWwindow* window, float deltaTime)
{
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
        if (firstClick)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
            firstClick = false;
            glfwGetCursorPos(window, &lastMousePos.x, &lastMousePos.y);
        }
        MousePosition currentMousePos;
        glfwGetCursorPos(window, &currentMousePos.x, &currentMousePos.y);

        double dif_x = currentMousePos.x - lastMousePos.x;
        double dif_y = -(currentMousePos.y - lastMousePos.y);

        double offsetX = dif_x * mouseSensitivity * deltaTime;
        double offsetY = dif_y * mouseSensitivity * deltaTime;

        lastMousePos.x = currentMousePos.x;
        lastMousePos.y = currentMousePos.y;

        yaw += offsetX;
        pitch += offsetY;

        // Clamp pitch to prevent gimbal lock
        if (pitch > Config::Camera::MAX_PITCH)  pitch = Config::Camera::MAX_PITCH;
        if (pitch < Config::Camera::MIN_PITCH) pitch = Config::Camera::MIN_PITCH;
    }

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  
        firstClick = true;
    }
}

void Camera::updateShader(Shader& shader, const char* uniform)
{
    shader.enable();
    shader.setMat4(uniform, cameraView);
}

void Camera::update(GLFWwindow* window, float deltaTime, std::vector<std::shared_ptr<Shader>>& shaderList, const char* uniform)
{
    keyboardMovement(window, deltaTime);
    mouseMovement(window, deltaTime);

    // Looking
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch)); 
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    front = glm::normalize(front);

    glm::mat4 view;
    view = glm::lookAt(position, position + front, up);

    // Zooming
    glm::mat4 projection;
    projection = glm::perspective(glm::radians((float) fov), aspectRatio, nearPlane, farPlane);

    cameraView = projection * view;

    for (auto& shader : shaderList)
        updateShader(*shader, uniform);
}

void Camera::setPerspective(float aspectRatio, float nearPlane, float farPlane){
    this->aspectRatio = aspectRatio;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;
}  

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (camera) {
        float currentFov = camera->getFov();
        camera->setFov(currentFov - static_cast<float>(yoffset * Config::Camera::SCROLL_FOV_STEP));
    }
}