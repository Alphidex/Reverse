/**
 * @file ResourceManager.h
 * @brief Centralized resource management system
 * @details Manages loading, caching, and lifecycle of all game assets (textures, shaders, models)
 * to prevent duplicate loading and provide efficient resource management
 */

#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include "Texture.h"
#include "Shader.h"
#include "Model.h"
#include "Logger.h"

using std::string;
using std::shared_ptr;
using std::weak_ptr;
using std::unordered_map;

/**
 * @brief Centralized manager for all game resources
 * @details Singleton class that handles loading and caching of textures, shaders, and models.
 * Uses smart pointers for automatic memory management and weak pointers to track resource usage.
 * All resources are cached by path to prevent duplicate loading.
 */
class ResourceManager
{
public:
    /**
     * @brief Gets the singleton instance of ResourceManager
     * @return Reference to the ResourceManager instance
     */
    static ResourceManager& getInstance();
    
    // Delete copy constructor and assignment operator (singleton pattern)
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    
    /**
     * @brief Loads or retrieves a cached texture
     * @param filePath Path to the texture file
     * @param type Texture type identifier ("diffuse", "specular", etc.)
     * @return Shared pointer to the texture
     * @throws std::runtime_error if texture loading fails
     */
    shared_ptr<Texture> loadTexture(const string& filePath, const string& type);
    
    /**
     * @brief Loads or retrieves a cached shader program
     * @param vertexPath Path to vertex shader source file
     * @param fragmentPath Path to fragment shader source file
     * @return Shared pointer to the shader program
     * @throws std::runtime_error if shader compilation or linking fails
     */
    shared_ptr<Shader> loadShader(const string& vertexPath, const string& fragmentPath);
    
    /**
     * @brief Loads or retrieves a cached 3D model
     * @param path Path to the model file
     * @return Shared pointer to the model
     * @throws std::runtime_error if model loading fails
     */
    shared_ptr<Model> loadModel(const string& path);
    
    /**
     * @brief Clears all expired resources from caches
     * @details Removes resources that are no longer referenced by any external code
     */
    void cleanupExpiredResources();
    
    /**
     * @brief Gets statistics about currently loaded resources
     * @param textures Number of cached textures
     * @param shaders Number of cached shaders
     * @param models Number of cached models
     */
    void getResourceStats(size_t& textures, size_t& shaders, size_t& models) const;
    
    /**
     * @brief Clears all resource caches
     * @details Removes all cached resources. Resources still in use will remain valid
     * until all references are released.
     */
    void clearAll();
    
    /**
     * @brief Checks if a texture is already loaded
     * @param filePath Path to the texture file
     * @return True if texture is in cache
     */
    bool isTextureLoaded(const string& filePath) const;
    
    /**
     * @brief Checks if a shader is already loaded
     * @param shaderKey Combined key of vertex and fragment shader paths
     * @return True if shader is in cache
     */
    bool isShaderLoaded(const string& shaderKey) const;
    
    /**
     * @brief Checks if a model is already loaded
     * @param filePath Path to the model file
     * @return True if model is in cache
     */
    bool isModelLoaded(const string& filePath) const;

private:
    /**
     * @brief Private constructor (singleton pattern)
     */
    ResourceManager();
    
    /**
     * @brief Destructor - logs resource cleanup
     */
    ~ResourceManager();
    
    /**
     * @brief Generates a unique cache key for a shader
     * @param vertexPath Path to vertex shader
     * @param fragmentPath Path to fragment shader
     * @return Unique key string
     */
    string generateShaderKey(const string& vertexPath, const string& fragmentPath) const;
    
    // Resource caches using weak pointers to allow automatic cleanup
    unordered_map<string, weak_ptr<Texture>> textureCache;
    unordered_map<string, weak_ptr<Shader>> shaderCache;
    unordered_map<string, weak_ptr<Model>> modelCache;
    
    // Statistics tracking
    size_t totalTexturesLoaded = 0;
    size_t totalShadersLoaded = 0;
    size_t totalModelsLoaded = 0;
};
