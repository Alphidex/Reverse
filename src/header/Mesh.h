/**
 * @file Mesh.h
 * @brief Individual mesh representation with rendering capabilities
 * @details Encapsulates vertex data, indices, textures, and transformation state
 */

#pragma once

// System Packages
#include<vector>
#include<string>
#include<memory>

// External Packages
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

// Project Packages
#include "CoreTypes.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Shader.h"

using std::vector, std::string, std::shared_ptr;

/**
 * @brief Represents a single renderable mesh with geometry and textures
 * @details Manages vertex buffers, element buffers, and transformation matrices
 */
class Mesh
{
public:
    /**
     * @brief Constructs a mesh with geometry and texture data
     * @param vertices Vertex data (positions, normals, texture coordinates)
     * @param indices Element indices for indexed drawing
     * @param textures Shared pointers to textures to apply to this mesh
     */
    Mesh(vector<Vertex>& vertices, vector<unsigned int>& indices, vector<shared_ptr<Texture>>& textures);
    
    /**
     * @brief Renders the mesh using the specified shader
     * @param shader Shader program to use
     * @param uniform Name of the model matrix uniform in the shader
     */
    void Draw(Shader& shader, const char* uniform) const;
    
    /**
     * @brief Frees GPU resources
     */
    void Delete();
    
    /**
     * @brief Sets the mesh's world position
     * @param position New position vector
     */
    void setPosition(glm::vec3 position);
    
    /**
     * @brief Sets the mesh's rotation
     * @param rotationDegrees Rotation angle in degrees
     * @param axis Rotation axis
     */
    void setRotation(float rotationDegrees, glm::vec3 axis);
    
    /**
     * @brief Sets the mesh's scale
     * @param scale Scale vector for each axis
     */
    void setScale(glm::vec3 scale);
    
private:
    vector<Vertex> vertices;           ///< Vertex data
    vector<unsigned int> indices;      ///< Element indices
    vector<shared_ptr<Texture>> textures; ///< Texture list (shared pointers)
    vector<string> textureUniforms;    ///< Texture uniform names
    
    VAO vao;  ///< Vertex Array Object
    EBO ebo;  ///< Element Buffer Object
    VBO vbo;  ///< Vertex Buffer Object

    glm::vec3 position = glm::vec3(0, 0, 0);    ///< World position
    float rotation = 0.0f;                       ///< Rotation angle (radians)
    glm::vec3 rotationAxis = glm::vec3(0, 0, 1); ///< Rotation axis
    glm::vec3 scale = glm::vec3(1, 1, 1);        ///< Scale factors
};