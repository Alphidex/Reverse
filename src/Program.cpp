/**
 * @file Program.cpp
 * @brief Implementation of the Program class
 */

#include "header/Program.h"

// Callback Functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

Program::Program(int width, int height)
{   
    if (!glfwInit()){
        std::cout << "Failed to initialize GLFW" << std::endl;
        ERROR = true;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Reverse", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        ERROR = true;
    }

    if (!ERROR)
    {
        glfwMakeContextCurrent(window);

        gladLoadGL();
        glViewport(0, 0, width, height);

        // Callback + Settings
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSwapInterval(1); // use Vsync 

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_STENCIL_TEST);
        glStencilMask(0x000F);
    }
}

void Program::ProcessEvents()
{
    glfwPollEvents();
    processInput(window);
}

void Program::SwapBuffers()
{
    glfwSwapBuffers(window);
}

void Program::ClearBuffers()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Program::Terminate()
{
    glfwTerminate();
}

bool Program::Running() const {
    return !glfwWindowShouldClose(window);
}

GLFWwindow* Program::GetWindow() const {
    return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
