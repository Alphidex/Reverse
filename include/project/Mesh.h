#ifndef MESH_H
#define MESH_H

#include<vector>

#include<project/Optional.h>
#include<project/VAO.h>
#include<project/Texture.h>

class Mesh
{
private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    // VAO VAO;
    
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures);
};

#endif