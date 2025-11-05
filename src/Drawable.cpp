// System Packages
#include<vector>
#include<string>
using std::vector;

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

// Generic Drawable Class. Anything that draws should inherit from it.
// Responsible for managing the buffer stack.
// Every object should have its own implementation of Draw.
class Drawable{
public:
    Drawable(vector<Vertex>& vertices, vector<unsigned int>& indices, vector<Texture>& textures);
    void Draw(Shader& shader, const char* uniform);

private:
    vector<Vertex> Vertices;
    vector<unsigned int> Indices;
    vector<Texture> Textures;
    VAO vao;
    VBO vbo;
    EBO ebo;
};


Drawable::Drawable(vector<Vertex>& vertices, vector<unsigned int>& indices, vector<Texture>& textures): 
Vertices(vertices), Indices(indices), Textures(textures),
vao(),
vbo(vertices.data(), vertices.size() * sizeof(Vertex)),
ebo(indices.data(), indices.size() * sizeof(unsigned int))
{
    vao.Bind();
    vbo.Bind();
    ebo.Bind();

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::Position));
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::Normal));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::TexCoord));

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}
