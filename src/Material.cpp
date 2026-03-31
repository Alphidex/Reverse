/**
 * @file Material.cpp
 * @brief Implementation of the Material class
 */

#include "header/Material.h"
#include "header/Logger.h"

Material::Material(std::shared_ptr<Shader> shader) : shader(shader) {
    if (!shader) {
        LOG_ERROR("Material created with null shader");
        throw std::invalid_argument("Material requires a valid shader");
    }
}

void Material::use() const {
    if (!shader) {
        LOG_ERROR("Attempting to use material with null shader");
        return;
    }
    
    // Activate the shader
    shader->enable();
    
    // Bind all textures
    int diffuseNum = 0;
    int specularNum = 0;
    int normalNum = 0;
    
    for (size_t i = 0; i < textures.size(); ++i) {
        const auto& texture = textures[i];
        std::string type = texture->getType();
        std::string uniformName;
        
        // Construct uniform name based on texture type
        if (type == "diffuse") {
            uniformName = "material.diffuse" + (diffuseNum > 0 ? std::to_string(diffuseNum) : "");
            diffuseNum++;
        }
        else if (type == "specular") {
            uniformName = "material.specular" + (specularNum > 0 ? std::to_string(specularNum) : "");
            specularNum++;
        }
        else if (type == "normal") {
            uniformName = "material.normal" + (normalNum > 0 ? std::to_string(normalNum) : "");
            normalNum++;
        }
        else {
            // Generic texture name
            uniformName = type + std::to_string(i);
        }
        
        texture->bind(*shader, uniformName.c_str(), static_cast<int>(i));
    }
    
    // Set material properties as uniforms
    shader->setVec3("material.diffuseColor", diffuseColor);
    shader->setVec3("material.specularColor", specularColor);
    shader->setVec3("material.ambientColor", ambientColor);
    shader->setFloat("material.shininess", shininess);
    shader->setFloat("material.alpha", alpha);
}

std::shared_ptr<Shader> Material::getShader() const {
    return shader;
}

// ===== Texture Management =====

void Material::addTexture(std::shared_ptr<Texture> texture) {
    if (texture) {
        textures.push_back(texture);
    }
    else {
        LOG_WARNING("Attempted to add null texture to material");
    }
}

const std::vector<std::shared_ptr<Texture>>& Material::getTextures() const {
    return textures;
}

void Material::clearTextures() {
    textures.clear();
}

// ===== Material Properties - Setters =====

void Material::setDiffuseColor(const glm::vec3& color) {
    diffuseColor = color;
}

void Material::setSpecularColor(const glm::vec3& color) {
    specularColor = color;
}

void Material::setAmbientColor(const glm::vec3& color) {
    ambientColor = color;
}

void Material::setShininess(float shin) {
    shininess = shin;
}

void Material::setAlpha(float a) {
    alpha = glm::clamp(a, 0.0f, 1.0f);
}

// ===== Material Properties - Getters =====

const glm::vec3& Material::getDiffuseColor() const {
    return diffuseColor;
}

const glm::vec3& Material::getSpecularColor() const {
    return specularColor;
}

const glm::vec3& Material::getAmbientColor() const {
    return ambientColor;
}

float Material::getShininess() const {
    return shininess;
}

float Material::getAlpha() const {
    return alpha;
}
