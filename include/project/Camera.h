#ifndef CAMERA_H
#define CAMERA_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

class Camera
{
public:
    bool firstClick = true;
    float Yaw = -90.0f;
    float Pitch = 0;
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 Position;
    glm::vec3 Front;

    float MovementSpeed = 0.25f;
    float MouseSensitivity = 0.1f;

    Camera(glm::vec3 Position);
    glm::mat4 Inputs(GLFWwindow* window);

private:
    struct MousePosition{
        double x;
        double y;
    };
    MousePosition lastMousePos;
};

void Scroll_Callback(GLFWwindow* window, double xoffset, double yoffset);

#endif