/**
 * @file Program.h
 * @brief GLFW and OpenGL context initialization and management
 * @details Top-level container for engine window and OpenGL configuration
 */

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

/**
 * @brief Manages the application window and OpenGL context
 * @details Handles GLFW initialization, window creation, and OpenGL settings.
 * Does not contain game-specific objects like Camera or Shaders.
 */
class Program
{
public:
    /**
     * @brief Initializes GLFW, creates window, and sets up OpenGL context
     * @param width Window width in pixels
     * @param height Window height in pixels
     */
    Program(int width, int height);
    
    /**
     * @brief Gets the GLFW window handle
     * @return Pointer to the GLFW window
     */
    GLFWwindow* getWindow() const;
    
    /**
     * @brief Processes window events and input
     */
    void processEvents();
    
    /**
     * @brief Swaps front and back buffers
     */
    void swapBuffers();
    
    /**
     * @brief Clears color, depth, and stencil buffers
     */
    void clearBuffers();
    
    /**
     * @brief Terminates GLFW and cleans up resources
     */
    void terminate();
    
    /**
     * @brief Checks if the window should remain open
     * @return True if window is still running
     */
    bool isRunning() const;

private:
    GLFWwindow* window; ///< GLFW window handle
    bool ERROR;          ///< Initialization error flag
};
