#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<vector>
#include "Shader.h"

struct MousePosition 
{
    double x, y;
};

class Camera
{
public:
    Camera(glm::vec3 position);
    void Update(GLFWwindow* window, float deltaTime, std::vector<Shader>& shaderList, const char* uniform);

private:
    glm::vec3 front;
    glm::vec3 position;
    bool firstClick = true;
    float yaw = -90.0f;
    float pitch = 0.0f;
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    MousePosition lastMousePos;

    float baseMovementSpeed = 30.0f;
    float shiftMovementSpeed = 90.0f;
    // movementSpeed is changed to shiftMovementSpeed when shift is held
    float movementSpeed = baseMovementSpeed;
    float mouseSensitivity = 1.0f;

    glm::mat4 cameraView = glm::mat4(1.0f);

    void KeyboardMovement(GLFWwindow* window, float deltaTime);
    void MouseMovement(GLFWwindow* window, float deltaTime);
    void UpdateShader(Shader& shader, const char* uniform);
};

void Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset);

