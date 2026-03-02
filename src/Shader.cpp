/**
 * @file Shader.cpp
 * @brief Implementation of the Shader class
 */

#include "header/Shader.h"
#include "header/Utilities.h"
#include <stdexcept>

Shader::Shader(const char* vertexPath, const char* fragmentPath)  {
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