#include<project/Camera.h>
#include<iostream>

double Fov = 45;

Camera::Camera(glm::vec3 position) : Position(position) {}

void Camera::KeyboardMovement(GLFWwindow* window, double deltaTime)
{
    float calibratedMovementSpeed = deltaTime * MovementSpeed;

    // Movement
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Position += Front * calibratedMovementSpeed;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Position -= Front * calibratedMovementSpeed;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Position += glm::normalize(glm::cross(Front, Up)) * calibratedMovementSpeed;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Position -= glm::normalize(glm::cross(Front, Up)) * calibratedMovementSpeed;
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        Position += Up * calibratedMovementSpeed;
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        Position -= Up * calibratedMovementSpeed;
    // Shifting
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        MovementSpeed = shiftMovementSpeed;
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        MovementSpeed = baseMovementSpeed;
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
}

void Camera::UpdateShader(Shader& shader, const char* uniform)
{
    shader.Enable();
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(CameraView));
}

void Camera::Update(GLFWwindow* window, double deltaTime, std::vector<Shader>& shaderList, const char* uniform)
{
    KeyboardMovement(window, deltaTime);
    MouseMovement(window);

    // Looking
    Front.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
    Front.y = sin(glm::radians(Pitch)); 
    Front.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
    Front = glm::normalize(Front);

    glm::mat4 view;
    view = glm::lookAt(Position, Position + Front, Up);

    // Zooming
    glm::mat4 projection;
    projection = glm::perspective(glm::radians((float) Fov), 800.0f / 600.0f, 0.1f, 1000.0f);

    CameraView = projection * view;

    for (Shader& shader : shaderList)
        UpdateShader(shader, uniform);
}

void Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset){
    Fov -= yoffset * 2;
    if (Fov < 1.0f) Fov = 1.0f;
    if (Fov > 45.0f) Fov = 45.0f;
}