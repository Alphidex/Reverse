#include <project/Interface.h>
#include<iostream>

Interface::Interface(GLFWwindow* window, Shader& shader) : window(window), shader(shader) 
{
    
};

bool Interface::IsOpen()
{
    return !glfwWindowShouldClose(window);
}

void Interface::ClearBackgroundColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
}

Container Interface::CreateContainer(float x, float y, float width, float height)
{
    Container container(x, y, width, height, window, shader);
    return container;
}

void Interface::DrawContainer(Container& container)
{
    container.Draw();
}



/*
topleft is (0, 0)
bottom right is (1,1)
*/
Container::Container(float x, float y, float width, float height, GLFWwindow* window, Shader& shader)
{
    // Checks for x and y
    assert(0.0f <= x && x <= 1.0f);
    assert(0.0f <= y && y <= 1.0f);
    assert(0.0f <= width && width <= 1.0f && x + width < 1.0f);
    assert(0.0f <= height && height <= 1.0f && y + height < 1.0f);

    /* Process parameters to NDC */ 
    // Get window size
    int winWidth, winHeight;
    glfwGetWindowSize(window, &winWidth, &winHeight);

    float nWidth = width  * 2.0f;
    float nHeight = height * 2.0f;
    float xNDC = (x * 2.0f) - 1.0f;
    float yNDC = -(y * 2.0f - 1.0f);
    
    std::vector<Vertex> vertices = {
        {{xNDC, yNDC, 0.0f}},
        {{xNDC, yNDC - nHeight, 0.0f}},
        {{xNDC + nWidth, yNDC, 0.0f}},
        {{xNDC + nWidth, yNDC - nHeight, 0.0f}}
    };
    
    std::vector<unsigned int> indices = {
        0, 1, 2,
        1, 2, 3
    };

    brush = Drawable(shader, vertices, indices);
}

void Container::Draw()
{
    brush.Draw();
}

void Container::Delete()
{
    brush.Delete();
}