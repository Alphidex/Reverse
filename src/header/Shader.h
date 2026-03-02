/**
 * @file Shader.h
 * @brief OpenGL shader program management
 * @details Compiles, links, and manages GLSL shader programs
 */

#pragma once

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

using std::string;

/**
 * @brief Manages an OpenGL shader program
 * @details Handles vertex and fragment shader compilation, linking, and lifecycle
 */
class Shader
{
public:
    /**
     * @brief Constructs and compiles a shader program from file paths
     * @param vertexPath Path to vertex shader source file
     * @param fragmentPath Path to fragment shader source file
     * @throws std::runtime_error if shader compilation or linking fails
     */
    Shader(const char* vertexPath, const char* fragmentPath);
    
    /**
     * @brief Gets the OpenGL shader program ID
     * @return The shader program ID
     */
    GLuint getID() const;
    
    /**
     * @brief Activates this shader program for rendering
     */
    void Enable() const;
    
    /**
     * @brief Deletes the shader program and frees GPU resources
     */
    void Delete();

private:
    GLuint ID; ///< OpenGL shader program identifier
    
    /**
     * @brief Checks for shader compilation/linking errors and throws if found
     * @param shader Shader or program ID to check
     * @param type "SHADER" for shader compilation, "PROGRAM" for linking
     * @throws std::runtime_error if errors are found
     */
    void compileErrors(unsigned int shader, const string& type);
};