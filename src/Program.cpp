/**
 * @file Program.cpp
 * @brief Implementation of the Program class
 */

#include "header/Program.h"
#include "header/Config.h"
#include "header/Logger.h"
#include <stdexcept>

// Callback Functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

Program::Program(int width, int height)
{   
    LOG_INFO("Initializing GLFW...");
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Config::Window::OPENGL_MAJOR_VERSION);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Config::Window::OPENGL_MINOR_VERSION);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    LOG_INFO("Creating window " + std::to_string(width) + "x" + std::to_string(height));
    window = glfwCreateWindow(width, height, Config::Window::WINDOW_TITLE, NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);

    LOG_INFO("Initializing GLAD...");
    if (!gladLoadGL()) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }
    
    // Log OpenGL info
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    LOG_INFO("OpenGL Renderer: " + std::string(reinterpret_cast<const char*>(renderer)));
    LOG_INFO("OpenGL Version: " + std::string(reinterpret_cast<const char*>(version)));
    
    glViewport(0, 0, width, height);

    // Callback + Settings
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(Config::Window::ENABLE_VSYNC ? 1 : 0);

    // Enable depth testing and stencil testing
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilMask(0x000F);
    
    ERROR = false;
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
