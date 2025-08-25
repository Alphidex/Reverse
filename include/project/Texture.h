#ifndef TEXTURE_H
#define TEXTURE_H

#include<glad/glad.h>
#include<stb/stb_image.h>
#include<iostream>

class Texture
{
public:
    GLuint ID;
    GLint texUnit;

    Texture(const char* filePath, int texUnit);
    void Bind();

};

#endif