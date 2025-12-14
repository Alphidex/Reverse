#pragma once

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

using std::string;

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    GLuint getID();
    void Enable();
    void Delete();

private:
    GLuint ID;
    void compileErrors(unsigned int& shader, string type);
};