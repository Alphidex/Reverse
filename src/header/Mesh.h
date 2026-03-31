/**
 * @file Mesh.h
 * @brief Individual mesh representation with rendering capabilities
 * @details Encapsulates vertex data, indices, and textures
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
#include "Material.h"

using std::vector, std::string, std::shared_ptr;

/**
 * @brief Represents a single renderable mesh with geometry and textures
 * @details Manages vertex buffers and element buffers
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
    Mesh(const vector<Vertex>& vertices, const vector<unsigned int>& indices, const vector<shared_ptr<Texture>>& textures);
    
    /**
     * @brief Constructs a mesh with a material
     * @param vertices Vertex data (positions, normals, texture coordinates)
     * @param indices Element indices for indexed drawing
     * @param material Shared pointer to the material to use for rendering
     */
    Mesh(const vector<Vertex>& vertices, const vector<unsigned int>& indices, shared_ptr<Material> material);
    
    /**
     * @brief Renders the mesh using the specified shader
     * @param shader Shader program to use
     * @param uniform Name of the model matrix uniform in the shader
     */
    void draw(Shader& shader, const char* uniform) const;
    
    /**
     * @brief Renders the mesh using its assigned material
     * @details Automatically binds the material and sets the model matrix
     */
    void draw() const;

    /**
     * @brief Renders the mesh using its assigned material and a provided model matrix
     * @param model Model matrix to use for rendering
     */
    void draw(const glm::mat4& model) const;
    
    /**
     * @brief Sets the material for this mesh
     * @param material Shared pointer to the material
     */
    void setMaterial(shared_ptr<Material> material);
    
    /**
     * @brief Gets the material of this mesh
     * @return Shared pointer to the material, or nullptr if not set
     */
    shared_ptr<Material> getMaterial() const;
    
    shared_ptr<Material> material;     ///< Material for rendering (optional)
    
private:
    vector<Vertex> vertices;           ///< Vertex data
    vector<unsigned int> indices;      ///< Element indices
    vector<shared_ptr<Texture>> textures; ///< Texture list (shared pointers)
    vector<string> textureUniforms;    ///< Texture uniform names
    
    VAO vao;  ///< Vertex Array Object
    EBO ebo;  ///< Element Buffer Object
    VBO vbo;  ///< Vertex Buffer Object

};