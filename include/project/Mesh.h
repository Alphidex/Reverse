#ifndef MESH_H
#define MESH_H

#include<vector>

#include<project/Optional.h>
#include<project/VAO.h>
#include<project/VBO.h>
#include<project/EBO.h>
#include<project/Texture.h>

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Texture texture;
    
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, Texture& texture);
    void Draw();
    void Delete();
    
private:
    VAO vao;
    EBO ebo;
    VBO vbo;
};

#endif