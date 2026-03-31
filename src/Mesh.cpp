/**
 * @file Mesh.cpp
 * @brief Implementation of the Mesh class
 */

#include "header/Mesh.h"
#include "header/Logger.h"
#include <stdexcept>

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<shared_ptr<Texture>>& textures): 
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

Mesh::Mesh(const vector<Vertex>& vertices, const vector<unsigned int>& indices, shared_ptr<Material> material): 
vertices(vertices), indices(indices), material(material),
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

void Mesh::draw(Shader& shader, const char* uniform) const {
    if (!uniform) {
        LOG_ERROR("Mesh::draw called with invalid uniform name");
        throw std::invalid_argument("Mesh::draw requires a valid model uniform name");
    }

    shader.enable();
    
    // Apply transformation matrix
    glm::mat4 model = glm::mat4(1.0f);
    shader.setMat4(uniform, model);

    // Bind textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++) {
        if (!textures[i]) {
            LOG_ERROR("Mesh::draw encountered null texture at index " + std::to_string(i));
            throw std::runtime_error("Mesh::draw cannot bind null texture");
        }

        std::string number;
        std::string texType = textures[i]->getType();
        
        if (texType == "diffuse")
            number = std::to_string(diffuseNr++);
        else if (texType == "specular")
            number = std::to_string(specularNr++);

        const char* name = "diffuse[0]";  // TODO: Make this dynamic
        textures[i]->bind(shader, name, i);
    }

    // Render mesh
    vao.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.unbind();
}

void Mesh::draw() const {
    draw(glm::mat4(1.0f));
}

void Mesh::draw(const glm::mat4& model) const {
    if (!material) {
        LOG_ERROR("Mesh::draw called without a material");
        throw std::runtime_error("Mesh::draw requires a valid material");
    }
    
    // Use material (binds shader and textures)
    material->use();
    
    auto shader = material->getShader();
    if (!shader) {
        LOG_ERROR("Mesh::draw encountered material with null shader");
        throw std::runtime_error("Mesh::draw requires material with valid shader");
    }

    shader->setMat4("model", model);
    
    // Render mesh
    vao.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.unbind();
}

void Mesh::setMaterial(shared_ptr<Material> mat) {
    material = mat;
}

shared_ptr<Material> Mesh::getMaterial() const {
    return material;
}
