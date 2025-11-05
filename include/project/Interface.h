#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <vector>
#include <project/Optional.h>
#include <project/Mesh.h>

class Interface
{
public:
    Interface(int width, int height, GLFWwindow* window);
    bool IsOpen();
    void ClearBackgroundColor(float r, float g, float b, float a);
    void CreateContainer(int x, int y, int width, int height);

private:
    int width;
    int height;
    GLFWwindow* window;
};

// Fancy name for 2D box: Though the implimentation will change later to make it more abstract
class Container
{
public:
    Container(int x, int y, int width, int height, GLFWwindow* window);
    void Draw();
private:
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    Mesh Box2D;
};