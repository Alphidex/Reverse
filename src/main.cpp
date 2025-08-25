// System Packages
#include<iostream>
#include<stdexcept>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include<filesystem>
#include<thread>
#include<chrono>
#include<vector>

// External Packages
#include<glad/glad.h> // Assigns function pointers since OpenGL is a specification
#include<GLFW/glfw3.h> // Create windows, assign context, poll events
#include<stb/stb_image.h>
#include<glm/glm.hpp>

// Project Packages
#include<project/Shader.h>
#include<project/VAO.h>
#include<project/VBO.h>
#include<project/EBO.h>
#include<project/Texture.h>
#include<project/Optional.h>


// Parameters
int width = 800;
int height = 800;

// Callback Functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
std::string getFileContents(const char* filename);
void shaderErrors(unsigned int& shader, std::string type);

// Data
std::vector<Vertex> vertices = {
    {{ 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f}}, //topright
    {{ 0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}}, //bottomright
    {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}}, //bottomleft
    {{-0.5f,  0.5f, 0.0f}, {0.0f, 1.0f}} //bottomleft
};

unsigned int indices[] = {  
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
}; 

int main(){
    // As it starts out in: "C:\\Users\\.User\\Desktop\\Reverse\\out\\build\\default"
    std::filesystem::current_path(std::filesystem::path(__FILE__).parent_path().parent_path());
    std::cout << "Working directory: " << std::filesystem::current_path() << std::endl;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Reverse", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    gladLoadGL();
    glViewport(0, 0, width, height);
 
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 
    
    // Shader Setup
    Shader shaderProgram("shader/default.vert", "shader/default.frag");

    // Buffer Setup
    VAO VAO;
    VBO VBO(vertices);
    EBO EBO(indices, sizeof(indices));

    VAO.Bind();
    VBO.Bind();
    EBO.Bind();

    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 5*sizeof(float), (void*)0);
    VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, 5*sizeof(float), (void*)(3*sizeof(float)));

    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();

    // Texture
    Texture texture("resource/wall.jpg", 0);


    // Curious what happens if I keep it out of while loop
    shaderProgram.Enable();
    glUniform1i(glGetUniformLocation(shaderProgram.ID, "sampledTexture"), 0);

    while(!glfwWindowShouldClose(window))
    {   
        processInput(window);

        // Clears the back-buffer with said color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Drawing
        VAO.Bind();
        texture.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(indices[0]), GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    VAO.Delete();
    VBO.Delete();
    EBO.Delete();
    shaderProgram.Delete();
    
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
