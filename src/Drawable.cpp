// External Packages
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "header/Drawable.h"
#include "header/CoreTypes.h"

Drawable::Drawable(Shader& shader, vector<Vertex>& vertices, vector<unsigned int>& indices, vector<Texture>& textures): 
shader(shader),
vertices(vertices), indices(indices), textures(textures),
vao(),
vbo(vertices.data(), vertices.size() * sizeof(Vertex)),
ebo(indices.data(), indices.size() * sizeof(unsigned int))
{
    vao.bind();
    vbo.bind();
    ebo.bind();

    vao.linkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::Position));
    vao.linkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::Normal));
    vao.linkAttrib(vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::TexCoord));
    
    vao.unbind();
    vbo.unbind();
    ebo.unbind();
}

void Drawable::Draw()
{
    shader.enable();

    vao.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.unbind();
}