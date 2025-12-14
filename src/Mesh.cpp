#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures): 
vertices(vertices), indices(indices), textures(textures),
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

void Mesh::Draw(Shader& shader, const char* uniform)
{
    shader.Enable();
    
    // Transformations
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, rotation, rotationAxis);
    model = glm::scale(model, scale);
    glUniformMatrix4fv(glGetUniformLocation(shader.getID(), uniform), 1, GL_FALSE, glm::value_ptr(model));

    // Drawing
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        std::string number;
        std::string texType = textures[i].getType();
        if(texType == "diffuse")
            number = std::to_string(diffuseNr++);
        else if(texType == "specular")
            number = std::to_string(specularNr++);

        // const char* name = ("material." + texType + "[" + number + "]").c_str();
        const char* name = "diffuse[0]";
        textures[i].Bind(shader, name, i);
    }

    vao.Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.Unbind();
}

void Mesh::Delete()
{
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
}

void Mesh::setPosition(glm::vec3 position)
{   
    this->position = position;
}

void Mesh::setRotation(float rotationDegrees, glm::vec3 axis)
{
    this->rotation = glm::radians(rotationDegrees);
    this->rotationAxis = axis;
}

void Mesh::setScale(glm::vec3 scale){
    this->scale = scale;
}