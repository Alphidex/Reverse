#include<project/Camera.h>
#include<iostream>

Camera::Camera(glm::vec3 position, glm::vec3 direction) : Position(position), Front(direction) {}

glm::mat4 Camera::Inputs(GLFWwindow* window)
{

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Position += Front * MovementSpeed;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Position -= Front * MovementSpeed;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Position += glm::normalize(glm::cross(Front, Up)) * MovementSpeed;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Position -= glm::normalize(glm::cross(Front, Up)) * MovementSpeed;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        if (firstClick)
        {
            double xPos, yPos;
            glfwGetCursorPos(window, &xPos, &yPos);
        }
        double newXPos, newYPos; 
        glfwGetCursorPos(window, &newXPos, &newYPos);
        float xOffset = newXPos - xPos;
        float yOffset = yPos - newYPos;

        Pitch += yOffset * MouseSensitivity;
        Yaw += xOffset * MouseSensitivity;

        if (Pitch > 89.0f) Pitch = 89.0f;
        if (Pitch < -89.0f) Pitch = -89.0f;

        Front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front.y = sin(glm::radians(Pitch));
        Front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(Front);
        }
    
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;  
	}

    glm::mat4 view;
    view = glm::lookAt(Position, Position + Front, Up);
    return view;
}