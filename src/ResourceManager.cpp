/**
 * @file ResourceManager.cpp
 * @brief Implementation of centralized resource management
 */

#include "header/ResourceManager.h"
#include <algorithm>

ResourceManager::ResourceManager() {
    LOG_INFO("ResourceManager initialized");
}

ResourceManager::~ResourceManager() {
    size_t textures = 0, shaders = 0, models = 0;
    getResourceStats(textures, shaders, models);
    LOG_INFO("ResourceManager shutting down - Final stats: " + 
             std::to_string(textures) + " textures, " +
             std::to_string(shaders) + " shaders, " +
             std::to_string(models) + " models");
}

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

shared_ptr<Texture> ResourceManager::loadTexture(const string& filePath, const string& type) {
    // Check if texture is already cached
    auto it = textureCache.find(filePath);
    if (it != textureCache.end()) {
        // Try to lock the weak pointer
        if (auto texture = it->second.lock()) {
            LOG_DEBUG("Texture cache hit: " + filePath);
            return texture;
        } else {
            // Weak pointer expired, remove from cache
            textureCache.erase(it);
        }
    }
    
    // Load new texture
    try {
        LOG_INFO("Loading texture: " + filePath);
        auto texture = std::make_shared<Texture>(filePath.c_str(), type.c_str());
        textureCache[filePath] = texture;
        totalTexturesLoaded++;
        LOG_DEBUG("Texture loaded successfully: " + filePath);
        return texture;
    } 
    catch (const std::exception& e) {
        LOG_ERROR("Failed to load texture '" + filePath + "': " + e.what());
        throw;
    }
}

shared_ptr<Shader> ResourceManager::loadShader(const string& vertexPath, const string& fragmentPath) {
    string key = generateShaderKey(vertexPath, fragmentPath);
    
    // Check if shader is already cached
    auto it = shaderCache.find(key);
    if (it != shaderCache.end()) {
        if (auto shader = it->second.lock()) {
            LOG_DEBUG("Shader cache hit: " + key);
            return shader;
        } else {
            shaderCache.erase(it);
        }
    }
    
    // Load new shader
    try {
        LOG_INFO("Loading shader: " + vertexPath + " + " + fragmentPath);
        auto shader = std::make_shared<Shader>(vertexPath.c_str(), fragmentPath.c_str());
        shaderCache[key] = shader;
        totalShadersLoaded++;
        LOG_DEBUG("Shader loaded successfully: " + key);
        return shader;
    } 
    catch (const std::exception& e) {
        LOG_ERROR("Failed to load shader '" + key + "': " + e.what());
        throw;
    }
}

shared_ptr<Model> ResourceManager::loadModel(const string& path) {
    // Check if model is already cached
    auto it = modelCache.find(path);
    if (it != modelCache.end()) {
        if (auto model = it->second.lock()) {
            LOG_DEBUG("Model cache hit: " + path);
            return model;
        } else {
            modelCache.erase(it);
        }
    }
    
    // Load new model
    try {
        LOG_INFO("Loading model: " + path);
        auto model = std::make_shared<Model>(path);
        modelCache[path] = model;
        totalModelsLoaded++;
        LOG_DEBUG("Model loaded successfully: " + path);
        return model;
    } 
    catch (const std::exception& e) {
        LOG_ERROR("Failed to load model '" + path + "': " + e.what());
        throw;
    }
}

void ResourceManager::cleanupExpiredResources() {
    size_t texturesRemoved = 0;
    size_t shadersRemoved = 0;
    size_t modelsRemoved = 0;
    
    // Remove expired textures
    for (auto it = textureCache.begin(); it != textureCache.end();) {
        if (it->second.expired()) {
            it = textureCache.erase(it);
            texturesRemoved++;
        } else {
            ++it;
        }
    }
    
    // Remove expired shaders
    for (auto it = shaderCache.begin(); it != shaderCache.end();) {
        if (it->second.expired()) {
            it = shaderCache.erase(it);
            shadersRemoved++;
        } else {
            ++it;
        }
    }
    
    // Remove expired models
    for (auto it = modelCache.begin(); it != modelCache.end();) {
        if (it->second.expired()) {
            it = modelCache.erase(it);
            modelsRemoved++;
        } else {
            ++it;
        }
    }
    
    if (texturesRemoved > 0 || shadersRemoved > 0 || modelsRemoved > 0) {
        LOG_DEBUG("Cleaned up expired resources: " + 
                  std::to_string(texturesRemoved) + " textures, " +
                  std::to_string(shadersRemoved) + " shaders, " +
                  std::to_string(modelsRemoved) + " models");
    }
}

void ResourceManager::getResourceStats(size_t& textures, size_t& shaders, size_t& models) const {
    textures = textureCache.size();
    shaders = shaderCache.size();
    models = modelCache.size();
}

void ResourceManager::clearAll() {
    size_t textures = textureCache.size();
    size_t shaders = shaderCache.size();
    size_t models = modelCache.size();
    
    textureCache.clear();
    shaderCache.clear();
    modelCache.clear();
    
    LOG_INFO("Cleared all resource caches: " + 
             std::to_string(textures) + " textures, " +
             std::to_string(shaders) + " shaders, " +
             std::to_string(models) + " models");
}

bool ResourceManager::isTextureLoaded(const string& filePath) const {
    auto it = textureCache.find(filePath);
    return it != textureCache.end() && !it->second.expired();
}

bool ResourceManager::isShaderLoaded(const string& shaderKey) const {
    auto it = shaderCache.find(shaderKey);
    return it != shaderCache.end() && !it->second.expired();
}

bool ResourceManager::isModelLoaded(const string& filePath) const {
    auto it = modelCache.find(filePath);
    return it != modelCache.end() && !it->second.expired();
}

string ResourceManager::generateShaderKey(const string& vertexPath, const string& fragmentPath) const {
    return vertexPath + "|" + fragmentPath;
}
