#ifndef CAMERA_H
#define CAMERA_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<project/Shader.h>
#include<vector>

class Camera
{
public:
    glm::vec3 Position;
    glm::vec3 Front;

    Camera(glm::vec3 Position);
    void Update(GLFWwindow* window, double deltaTime, std::vector<Shader>& shaderList, const char* uniform);

private:
    bool firstClick = true;
    float Yaw = -90.0f;
    float Pitch = 0;
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

    struct MousePosition 
    {
        double x;
        double y;
    };

    MousePosition lastMousePos;

    float baseMovementSpeed = 30;
    float shiftMovementSpeed = 90;

    float MovementSpeed = baseMovementSpeed;
    float MouseSensitivity = 0.1f;

    glm::mat4 CameraView = glm::mat4(1.0f);

    void KeyboardMovement(GLFWwindow* window, double deltaTime);
    void MouseMovement(GLFWwindow* window);
    void UpdateShader(Shader& shader, const char* uniform);
};

void Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset);

#endif