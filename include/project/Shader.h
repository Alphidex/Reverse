#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include"project/Optional.h"

class Shader
{
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);
    void Enable();
    void Delete();

private:
    void compileErrors(unsigned int& shader, std::string type);
};

#endif
