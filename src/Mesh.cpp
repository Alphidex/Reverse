#include<project/Mesh.h>

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, Texture& texture): 
vertices(vertices), indices(indices), texture(texture),
vao(),
vbo(vertices.data(), vertices.size() * sizeof(Vertex)),
ebo(indices.data(), indices.size() * sizeof(unsigned int))
{
    vao.Bind();
    vbo.Bind();
    ebo.Bind();

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 5*sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 5*sizeof(float), (void*)(3*sizeof(float)));

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}

void Mesh::Draw()
{
    // Drawing
    vao.Bind();
    texture.Bind();
    glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(indices[0]), GL_UNSIGNED_INT, 0);
    vao.Unbind();
}

void Mesh::Delete()
{
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
}