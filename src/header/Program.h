#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

/*
Top - level container for Game Engine configuration:
1. Settings
2. Start-up values
3. Should not contain: Camera, Shaders etc.

This is just a configurator for the GLFW, GLAD settings.
*/

class Program
{
public:
    Program(int width, int height);
    GLFWwindow* GetWindow();
    void ProcessEvents();
    void SwapBuffers();
    void ClearBuffers();
    void Terminate();
    bool Running();

private:
    GLFWwindow* window;
    bool ERROR;
};
