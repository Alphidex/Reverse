#include<project/Mesh.h>

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices): 
vertices(vertices), indices(indices),
vao(),
vbo(vertices.data(), vertices.size() * sizeof(Vertex)),
ebo(indices.data(), indices.size() * sizeof(unsigned int))
{
    vao.Bind();
    vbo.Bind();
    ebo.Bind();

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 9*sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 4, GL_FLOAT, 9*sizeof(float), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 9*sizeof(float), (void*)(7 * sizeof(float)));

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}

void Mesh::ChangeTexture(Texture& texture)
{
    this->texture = texture;
    drawTexture = true;
}

void Mesh::Draw(Shader& shader, const char* modelUniformLocation)
{
    shader.Enable();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, Position);
    model = glm::rotate(model, Rotation, RotationAxis);
    model = glm::scale(model, Scale);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, modelUniformLocation), 1, GL_FALSE, glm::value_ptr(model));

    // Drawing
    vao.Bind();
    if (drawTexture)
        texture.Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.Unbind();
}

void Mesh::Delete()
{
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
}

void Mesh::ChangePosition(glm::vec3 position)
{   
    Position = position;
}

void Mesh::ChangeRotation(float rotationDegrees, glm::vec3 axis)
{
    Rotation = glm::radians(rotationDegrees);
    RotationAxis = axis;
}

void Mesh::ChangeScale(glm::vec3 scale)
{
    Scale = scale;
}