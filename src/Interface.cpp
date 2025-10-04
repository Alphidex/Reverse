#include <project/Interface.h>
#include<iostream>

Interface::Interface(int width, int height, GLFWwindow* window) : width(width), height(height), window(window) {};

bool Interface::IsOpen()
{
    return !glfwWindowShouldClose(window);
}

void Interface::ClearBackgroundColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}