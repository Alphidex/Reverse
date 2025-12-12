#pragma once

// System Packages
#include<vector>
#include<string>

// External Packages
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

// Project Packages
#include "CoreTypes.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Shader.h"

using std::vector, std::string;

class Mesh
{
public:  
    Mesh(vector<Vertex>& vertices, vector<unsigned int>& indices, vector<Texture>& textures);
    void Draw(Shader& shader, const char* uniform);
    void Delete();
    void setPosition(glm::vec3 position);
    void setRotation(float rotationDegrees, glm::vec3 axis);
    void setScale(glm::vec3 scale);
    
private:
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    vector<string> textureUniforms;
    
    VAO vao;
    EBO ebo;
    VBO vbo;

    glm::vec3 position = glm::vec3(0, 0, 0);
    float rotation = 0.0f;
    glm::vec3 rotationAxis = glm::vec3(0, 0, 1);
    glm::vec3 scale = glm::vec3(1, 1, 1);
};