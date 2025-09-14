#include<project/Texture.h>

Texture::Texture() {};

Texture::Texture(const char* filePath, const char* type): Path(filePath), Type(type)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    // Wrapping/filtering options   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Image Loading
    stbi_set_flip_vertically_on_load(true);
    
    int width, height, nrChannels;
    unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
    if (data){
        GLenum imageType = nrChannels == 4 ? GL_RGBA : nrChannels == 3 ? GL_RGB : GL_RED;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, imageType, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
        std::cout << "Path Provided: " << Path << std::endl;
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind(Shader& shader, const char* uniform, int texUnit)
{
    glActiveTexture(GL_TEXTURE0 + texUnit);
    glBindTexture(GL_TEXTURE_2D, ID);
    glUniform1i(glGetUniformLocation(shader.ID, uniform), texUnit);  
}