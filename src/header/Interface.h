#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Shader.h"
#include "Drawable.h"
#include "CoreTypes.h"

using std::vector;

// UI Interface
class Interface
{
public:
    Interface(GLFWwindow* window, Shader& shader);
    bool IsOpen();
    void ClearBackgroundColor(float r, float g, float b, float a);

private:
    GLFWwindow* window;
    Shader shader;
};

// UI Container
class Container
{
public:
    Container(float x, float y, float width, float height, GLFWwindow* window, Shader& shader);
    ~Container();
    void Draw();
private:
    Drawable* brush;
    vector<Vertex> vertices;
    vector<GLuint> indices;
};