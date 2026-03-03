/**
 * @file Model.h
 * @brief 3D model loading and management using Assimp
 * @details Loads complex 3D models from various file formats and converts to internal Mesh representation
 */

#pragma once

#include<map>
#include<memory>
#include<string>
#include<vector>
// External Packages
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

// Project Packages
#include "Mesh.h"
using std::string, std::vector, std::map, std::shared_ptr;

/**
 * @brief Loads and renders 3D models from various file formats
 * @details Uses Assimp library to import models and converts them to internal Mesh representation.
 * Supports texture caching to avoid loading duplicate textures.
 */
class Model
{
public:
    /**
     * @brief Constructs a model by loading from file
     * @param path Path to the model file (supports OBJ, FBX, GLTF, etc.)
     * @throws std::runtime_error if model loading fails
     */
    Model(const string& path);
    
    /**
     * @brief Renders all meshes in the model
     * @param shader Shader program to use for rendering
     */
    void Draw(Shader& shader) const;

private:
    vector<Mesh> meshes;           ///< All meshes in this model
    string directory;              ///< Directory containing the model file
    
    /**
     * @brief Processes a scene node recursively
     * @param node Assimp node to process
     * @param scene The complete scene
     */
    void processNode(aiNode* node, const aiScene* scene);
    
    /**
     * @brief Converts an Assimp mesh to internal Mesh representation
     * @param mesh Assimp mesh to convert
     * @param scene The complete scene
     * @return Converted Mesh object
     */
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    
    /**
     * @brief Loads all textures of a specific type from a material
     * @param mat Assimp material containing textures
     * @param type Texture type to load (diffuse, specular, etc.)
     * @param typeName Internal name for the texture type
     * @return Vector of loaded texture shared pointers
     */
    vector<shared_ptr<Texture>> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const string& typeName);
};