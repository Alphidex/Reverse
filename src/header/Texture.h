#pragma once

#include<glad/glad.h>
#include<stb/stb_image.h>
#include<iostream>
#include<string>
#include "Shader.h"

using std::string;

class Texture
{
public:
    Texture();
    Texture(const char* filePath, const char* type);
    void Bind(Shader& shader, const char* uniform, int texUnit);
    string getType();
    
private:
    GLuint ID;
    string type {};
    string path {};
};