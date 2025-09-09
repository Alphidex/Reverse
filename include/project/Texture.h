#ifndef TEXTURE_H
#define TEXTURE_H

#include<glad/glad.h>
#include<stb/stb_image.h>
#include<iostream>
#include<project/Shader.h>
#include<string>

class Texture
{
public:
    std::string type {};
    Texture();
    Texture(const char* filePath, int texUnit);
    void Bind(Shader& shader, const char* uniform);

private:
    GLuint ID;
    GLint texUnit;
};

#endif