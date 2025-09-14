#ifndef OPTIONAL_H
#define OPTIONAL_H

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<glm/glm.hpp>

std::string readFile(std::string filename);

struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoord;
};

#endif