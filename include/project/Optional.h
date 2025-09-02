#ifndef OPTIONAL_H
#define OPTIONAL_H

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<glm/glm.hpp>

std::string readFile(std::string filename);

struct Vertex{
    glm::vec3 coord;
    glm::vec4 color;
    glm::vec2 texCoord;
    glm::vec3 normal;
};

#endif