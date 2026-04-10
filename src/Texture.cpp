/**
 * @file Texture.cpp
 * @brief Implementation of texture loading and management
 */

#include "header/Texture.h"
#include "header/Config.h"
#include "header/Logger.h"
#include <stdexcept>

Texture::Texture() {}

Texture::~Texture() {
    if (ID != 0) {
        glDeleteTextures(1, &ID);
        ID = 0;
    }
}

Texture::Texture(const char* filePath, const char* type) : path(filePath), type(type) {
    LOG_DEBUG("Loading texture: " + std::string(filePath));
    
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    // Set texture wrapping and filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image with configured vertical flip setting
    stbi_set_flip_vertically_on_load(Config::Textures::FLIP_VERTICALLY_ON_LOAD);
    
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
    
    if (data) {
        GLenum imageType = nrChannels == 4 ? GL_RGBA : nrChannels == 3 ? GL_RGB : GL_RED;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, imageType, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } 
    else {
        stbi_image_free(data);
        glBindTexture(GL_TEXTURE_2D, 0);
        throw std::runtime_error("Failed to load texture: " + std::string(filePath));
    }
    
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind(Shader& shader, const char* uniform, int texUnit) const {
    glActiveTexture(GL_TEXTURE0 + texUnit);
    glBindTexture(GL_TEXTURE_2D, ID);
    shader.setInt(uniform, texUnit);
}

string Texture::getType() const {
    return type;
}