#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

class Interface
{
public:
    Interface(int width, int height, GLFWwindow* window);
    bool IsOpen();
    void ClearBackgroundColor(float r, float g, float b, float a);
private:
    int width;
    int height;
    GLFWwindow* window;
};