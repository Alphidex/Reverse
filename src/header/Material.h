/**
 * @file Material.h
 * @brief Material system for managing shaders, textures, and properties
 * @details Bundles shader programs with textures and uniform values for rendering
 */

#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"

/**
 * @brief Represents a complete material for rendering
 * @details Bundles a shader program with textures and material properties.
 * Provides a unified interface for setting up rendering state.
 */
class Material
{
public:
    /**
     * @brief Constructs a material with a shader
     * @param shader Shared pointer to the shader program
     */
    Material(std::shared_ptr<Shader> shader);
    
    /**
     * @brief Activates this material for rendering
     * @details Enables the shader and binds all textures
     */
    void use() const;
    
    /**
     * @brief Gets the associated shader program
     * @return Shared pointer to the shader
     */
    std::shared_ptr<Shader> getShader() const;
    
    // ===== Texture Management =====
    
    /**
     * @brief Adds a texture to the material
     * @param texture Shared pointer to the texture
     */
    void addTexture(std::shared_ptr<Texture> texture);
    
    /**
     * @brief Gets all textures in the material
     * @return Vector of texture pointers
     */
    const std::vector<std::shared_ptr<Texture>>& getTextures() const;
    
    /**
     * @brief Clears all textures from the material
     */
    void clearTextures();
    
    // ===== Material Properties =====
    
    /**
     * @brief Sets the diffuse color
     * @param color RGB diffuse color
     */
    void setDiffuseColor(const glm::vec3& color);
    
    /**
     * @brief Sets the specular color
     * @param color RGB specular color
     */
    void setSpecularColor(const glm::vec3& color);
    
    /**
     * @brief Sets the ambient color
     * @param color RGB ambient color
     */
    void setAmbientColor(const glm::vec3& color);
    
    /**
     * @brief Sets the shininess factor
     * @param shininess Shininess value (typically 1-128)
     */
    void setShininess(float shininess);
    
    /**
     * @brief Sets the opacity/alpha value
     * @param alpha Opacity value (0.0 = transparent, 1.0 = opaque)
     */
    void setAlpha(float alpha);
    
    /**
     * @brief Gets the diffuse color
     * @return RGB diffuse color
     */
    const glm::vec3& getDiffuseColor() const;
    
    /**
     * @brief Gets the specular color
     * @return RGB specular color
     */
    const glm::vec3& getSpecularColor() const;
    
    /**
     * @brief Gets the ambient color
     * @return RGB ambient color
     */
    const glm::vec3& getAmbientColor() const;
    
    /**
     * @brief Gets the shininess factor
     * @return Shininess value
     */
    float getShininess() const;
    
    /**
     * @brief Gets the opacity/alpha value
     * @return Alpha value
     */
    float getAlpha() const;
    
private:
    std::shared_ptr<Shader> shader;                    ///< Associated shader program
    std::vector<std::shared_ptr<Texture>> textures;    ///< Material textures
    
    // Material properties
    glm::vec3 diffuseColor{1.0f, 1.0f, 1.0f};   ///< Diffuse color (default white)
    glm::vec3 specularColor{1.0f, 1.0f, 1.0f};  ///< Specular color (default white)
    glm::vec3 ambientColor{0.1f, 0.1f, 0.1f};   ///< Ambient color (default dark gray)
    float shininess{32.0f};                      ///< Shininess factor (default 32)
    float alpha{1.0f};                           ///< Opacity (default opaque)
};
