/**
 * @file Shader.cpp
 * @brief Implementation of the Shader class
 */

#include "header/Shader.h"
#include "header/Utilities.h"
#include "header/Logger.h"
#include <stdexcept>

Shader::Shader(const char* vertexPath, const char* fragmentPath)  {    LOG_DEBUG("Loading shaders: " + std::string(vertexPath) + ", " + std::string(fragmentPath));
        // Create shader objects
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Read shader source files
    std::string vertexCode = readFile(vertexPath);
    std::string fragmentCode = readFile(fragmentPath);

    const char* vertexShaderSource = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();
    
    // Compile shaders
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    glCompileShader(vertexShader);
    compileErrors(vertexShader, "SHADER");
    
    glCompileShader(fragmentShader);
    compileErrors(fragmentShader, "SHADER");

    // Link shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    compileErrors(ID, "PROGRAM");

    // Clean up shader objects (no longer needed after linking)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint Shader::getID() const {
    return ID;
}

void Shader::Enable() const {
    glUseProgram(ID);
}

void Shader::Delete() {
    glDeleteProgram(ID);
}

void Shader::compileErrors(unsigned int shader, const string& type) {
    GLint success;
    GLchar infoLog[1024];
    
    if (type == "SHADER") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            throw std::runtime_error("Shader compilation error: " + std::string(infoLog));
        }
    }
    else if (type == "PROGRAM") {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            throw std::runtime_error("Shader program linking error: " + std::string(infoLog));
        }
    }
}

// ===== Uniform Location Caching =====

GLint Shader::getUniformLocation(const string& name) const {
    // Check if location is already cached
    auto it = uniformLocationCache.find(name);
    if (it != uniformLocationCache.end()) {
        return it->second;
    }
    
    // Look up location and cache it
    GLint location = glGetUniformLocation(ID, name.c_str());
    if (location == -1) {
        LOG_WARNING("Uniform '" + name + "' not found in shader program");
    }
    uniformLocationCache[name] = location;
    return location;
}

// ===== Type-safe Uniform Setters =====

void Shader::setInt(const string& name, int value) {
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setFloat(const string& name, float value) {
    glUniform1f(getUniformLocation(name), value);
}

void Shader::setVec2(const string& name, const glm::vec2& value) {
    glUniform2fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setVec2(const string& name, float x, float y) {
    glUniform2f(getUniformLocation(name), x, y);
}

void Shader::setVec3(const string& name, const glm::vec3& value) {
    glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setVec3(const string& name, float x, float y, float z) {
    glUniform3f(getUniformLocation(name), x, y, z);
}

void Shader::setVec4(const string& name, const glm::vec4& value) {
    glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setVec4(const string& name, float x, float y, float z, float w) {
    glUniform4f(getUniformLocation(name), x, y, z, w);
}

void Shader::setMat3(const string& name, const glm::mat3& value) {
    glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setMat4(const string& name, const glm::mat4& value) {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}