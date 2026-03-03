/**
 * @file Shader.h
 * @brief OpenGL shader program management
 * @details Compiles, links, and manages GLSL shader programs with uniform caching
 */

#pragma once

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include<unordered_map>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

using std::string;

/**
 * @brief Manages an OpenGL shader program
 * @details Handles vertex and fragment shader compilation, linking, lifecycle, and uniform management with caching
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

    // ===== Type-safe uniform setters with automatic caching =====
    
    /**
     * @brief Sets an integer uniform
     * @param name Uniform name in shader
     * @param value Integer value to set
     */
    void setInt(const string& name, int value);
    
    /**
     * @brief Sets a float uniform
     * @param name Uniform name in shader
     * @param value Float value to set
     */
    void setFloat(const string& name, float value);
    
    /**
     * @brief Sets a vec2 uniform
     * @param name Uniform name in shader
     * @param value vec2 value to set
     */
    void setVec2(const string& name, const glm::vec2& value);
    
    /**
     * @brief Sets a vec2 uniform from components
     * @param name Uniform name in shader
     * @param x X component
     * @param y Y component
     */
    void setVec2(const string& name, float x, float y);
    
    /**
     * @brief Sets a vec3 uniform
     * @param name Uniform name in shader
     * @param value vec3 value to set
     */
    void setVec3(const string& name, const glm::vec3& value);
    
    /**
     * @brief Sets a vec3 uniform from components
     * @param name Uniform name in shader
     * @param x X component
     * @param y Y component
     * @param z Z component
     */
    void setVec3(const string& name, float x, float y, float z);
    
    /**
     * @brief Sets a vec4 uniform
     * @param name Uniform name in shader
     * @param value vec4 value to set
     */
    void setVec4(const string& name, const glm::vec4& value);
    
    /**
     * @brief Sets a vec4 uniform from components
     * @param name Uniform name in shader
     * @param x X component
     * @param y Y component
     * @param z Z component
     * @param w W component
     */
    void setVec4(const string& name, float x, float y, float z, float w);
    
    /**
     * @brief Sets a mat3 uniform
     * @param name Uniform name in shader
     * @param value mat3 value to set
     */
    void setMat3(const string& name, const glm::mat3& value);
    
    /**
     * @brief Sets a mat4 uniform
     * @param name Uniform name in shader
     * @param value mat4 value to set
     */
    void setMat4(const string& name, const glm::mat4& value);

private:
    GLuint ID; ///< OpenGL shader program identifier
    mutable std::unordered_map<string, GLint> uniformLocationCache; ///< Cache for uniform locations
    
    /**
     * @brief Gets a uniform location with caching to avoid redundant lookups
     * @param name Uniform name in shader
     * @return The uniform location, or -1 if not found
     */
    GLint getUniformLocation(const string& name) const;
    
    /**
     * @brief Checks for shader compilation/linking errors and throws if found
     * @param shader Shader or program ID to check
     * @param type "SHADER" for shader compilation, "PROGRAM" for linking
     * @throws std::runtime_error if errors are found
     */
    void compileErrors(unsigned int shader, const string& type);
};