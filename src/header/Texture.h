/**
 * @file Texture.h
 * @brief OpenGL texture management
 * @details Loads and manages 2D textures from image files
 */

#pragma once

#include<glad/glad.h>
#include<stb/stb_image.h>
#include<iostream>
#include<string>
#include "Shader.h"

using std::string;

/**
 * @brief Manages an OpenGL 2D texture
 * @details Loads textures from image files and binds them to shader programs
 */
class Texture
{
public:
    /**
     * @brief Default constructor (creates uninitialized texture)
     */
    Texture();
    
    /**
     * @brief Constructs a texture from an image file
     * @param filePath Path to the image file
     * @param type Texture type identifier ("diffuse", "specular", etc.)
     * @throws std::runtime_error if texture loading fails
     */
    Texture(const char* filePath, const char* type);
    
    /**
     * @brief Binds the texture to a specific texture unit for rendering
     * @param shader Shader program to bind to
     * @param uniform Name of the sampler uniform in the shader
     * @param texUnit Texture unit index (0-31)
     */
    void Bind(Shader& shader, const char* uniform, int texUnit) const;
    
    /**
     * @brief Gets the texture type identifier
     * @return Type string ("diffuse", "specular", etc.)
     */
    string getType() const;
    
private:
    GLuint ID;      ///< OpenGL texture identifier
    string type{};  ///< Texture type (diffuse, specular, etc.)
    string path{};  ///< File path of the texture
};