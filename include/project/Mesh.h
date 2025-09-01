#ifndef MESH_H
#define MESH_H

// System Packages
#include<vector>

// External Packages
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

// Project Packages
#include<project/Optional.h>
#include<project/VAO.h>
#include<project/VBO.h>
#include<project/EBO.h>
#include<project/Texture.h>
#include<project/Shader.h>

class Mesh
{
public:    
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
    void Draw(Shader& shader, const char* uniform);
    void Delete();
    void ChangeTexture(Texture& texture);
    void ChangePosition(glm::vec3 position);
    void ChangeRotation(float rotationDegrees, glm::vec3 axis);
    void ChangeScale(glm::vec3 scale);
    
private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Texture texture;
    bool drawTexture = false;
    
    VAO vao;
    EBO ebo;
    VBO vbo;

    glm::vec3 Position = glm::vec3(0, 0, 0);
    float Rotation = 0.0f;
    glm::vec3 RotationAxis = glm::vec3(0, 0, 1);
    glm::vec3 Scale = glm::vec3(1, 1, 1);
};

#endif