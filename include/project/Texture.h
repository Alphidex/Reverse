#ifndef TEXTURE_H
#define TEXTURE_H

#include<glad/glad.h>
#include<stb/stb_image.h>
#include<iostream>
#include<project/Shader.h>

class Texture
{
public:
    GLuint ID;
    GLint texUnit;

    Texture();
    Texture(const char* filePath, int texUnit);
    void Bind(Shader& shader, const char* uniform);
};

#endif