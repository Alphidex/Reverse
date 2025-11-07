// System Packages
#include<vector>
#include<string>
using std::vector;

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
    Drawable(Shader& shader, vector<Vertex>& vertices, vector<unsigned int>& indices, vector<Texture> textures = {});
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