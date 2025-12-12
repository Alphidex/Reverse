#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Shader.h"
#include "Drawable.h"

class Interface;
class Container;

class Interface
{
public:
    Interface(GLFWwindow* window, Shader& shader);
    bool IsOpen();
    void ClearBackgroundColor(float r, float g, float b, float a);
    Container CreateContainer(float x, float y, float width, float height);
    void DrawContainer(Container& contaienr);

private:
    GLFWwindow* window;
    Shader shader;
};

// Fancy name for 2D box: Though the implimentation will change later to make it more abstract
class Container
{
public:
    Container(float x, float y, float width, float height, GLFWwindow* window, Shader& shader);
    void Draw();
    void Delete();
private:
    Drawable* brush;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
};