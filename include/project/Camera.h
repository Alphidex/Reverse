#ifndef CAMERA_H
#define CAMERA_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glad/glad.h>
#include<glfw/glfw3.h>

class Camera
{
public:
    bool firstClick = true;
    float Yaw = -90.0f;
    float Pitch = 0;
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 Position;
    glm::vec3 Right;
    glm::vec3 Front;

    // camera options
    float MovementSpeed = 0.5;
    float MouseSensitivity = 1.0f;
    float Zoom;

    Camera(glm::vec3 Position, glm::vec3 Front);
    glm::mat4 Inputs(GLFWwindow* window);

private:
    float xPos = 0.0f;
    float yPos = 0.0f;
};

#endif