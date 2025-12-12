#pragma once

// System Packages
#include<vector>
#include<string>

// Project Packages
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Shader.h"


using std::vector;

// Generic Drawable Class. Anything that draws should inherit from it.
// Responsible for managing the buffer stack.
// Every object should have its own implementation of Draw.
class Drawable{
public:
    Drawable(Shader& shader, vector<Vertex>& vertices, vector<unsigned int>& indices, vector<Texture>& textures);
    void Draw();
    void Delete();

private:
    Shader shader;
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    VAO vao;
    VBO vbo;
    EBO ebo;
};