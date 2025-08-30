#include<project/Camera.h>
#include<iostream>

double Fov = 45;

Camera::Camera(glm::vec3 position) : Position(position) {}

glm::mat4 Camera::Inputs(GLFWwindow* window)
{
    // Movement
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Position += Front * MovementSpeed;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Position -= Front * MovementSpeed;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Position += glm::normalize(glm::cross(Front, Up)) * MovementSpeed;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Position -= glm::normalize(glm::cross(Front, Up)) * MovementSpeed;
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        Position += Up * MovementSpeed;
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        Position -= Up * MovementSpeed;
    // Shifting
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        MovementSpeed = 3;
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        MovementSpeed = 1;

    // Mouse Movement
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

        offsetX *= MouseSensitivity;
        offsetY *= MouseSensitivity;

        Yaw += offsetX;
        Pitch += offsetY;

        if (Pitch > 89.0f) Pitch = 89.0f;
        if (Pitch < -89.0f) Pitch = -89.0f;
    }

    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);  
        firstClick = true;
    }

    Front.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
    Front.y = sin(glm::radians(Pitch)); 
    Front.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
    Front = glm::normalize(Front);

    glm::mat4 view;
    view = glm::lookAt(Position, Position + Front, Up);

    // Zooming
    glm::mat4 projection;
    projection = glm::perspective(glm::radians((float) Fov), 800.0f / 600.0f, 0.1f, 100.0f);

    return projection * view;
}

void Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset){
    Fov -= yoffset * 2;
    if (Fov < 1.0f) Fov = 1.0f;
    if (Fov > 45.0f) Fov = 45.0f;
}