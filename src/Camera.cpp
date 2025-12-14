#include <iostream>
#include "Camera.h"

double fov = 45;

Camera::Camera(glm::vec3 position) : position(position) {}

void Camera::KeyboardMovement(GLFWwindow* window, double deltaTime)
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

void Camera::MouseMovement(GLFWwindow* window)
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

        double offsetX = currentMousePos.x - lastMousePos.x;
        double offsetY = -currentMousePos.y + lastMousePos.y;
        lastMousePos.x = currentMousePos.x;
        lastMousePos.y = currentMousePos.y;

        offsetX *= mouseSensitivity;
        offsetY *= mouseSensitivity;

        yaw += offsetX;
        pitch += offsetY;

        if (pitch > 89.0f)  pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
    }

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  
        firstClick = true;
    }
}

void Camera::UpdateShader(Shader& shader, const char* uniform)
{
    shader.Enable();
    glUniformMatrix4fv(glGetUniformLocation(shader.getID(), uniform), 1, GL_FALSE, glm::value_ptr(cameraView));
}

void Camera::Update(GLFWwindow* window, double deltaTime, std::vector<Shader>& shaderList, const char* uniform)
{
    KeyboardMovement(window, deltaTime);
    MouseMovement(window);

    // Looking
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch)); 
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    front = glm::normalize(front);

    glm::mat4 view;
    view = glm::lookAt(position, position + front, up);

    // Zooming
    glm::mat4 projection;
    projection = glm::perspective(glm::radians((float) fov), 800.0f / 600.0f, 0.1f, 1000.0f);

    cameraView = projection * view;

    for (Shader& shader : shaderList)
        UpdateShader(shader, uniform);
}

void Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset){
    fov -= yoffset * 2;
    if (fov < 1.0f) fov = 1.0f;
    if (fov > 45.0f) fov = 45.0f;
}