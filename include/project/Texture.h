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
    GLuint ID;
    std::string Type {};
    std::string Path {};
    Texture();
    Texture(const char* filePath, const char* type);
    void Bind(Shader& shader, const char* uniform, int texUnit);
};

#endif