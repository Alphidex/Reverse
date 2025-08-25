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

// External Packages
#include<glad/glad.h> // Assigns function pointers since OpenGL is a specification
#include<GLFW/glfw3.h> // Create windows, assign context, poll events
#include <stb/stb_image.h>

// Project Packages
#include<project/Shader.h>
#include<project/VAO.h>
#include<project/VBO.h>
#include<project/EBO.h>


// Parameters
int width = 800;
int height = 800;

// Callback Functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
std::string getFileContents(const char* filename);
void shaderErrors(unsigned int& shader, std::string type);

// Data
float vertices[] = {
    //    Coords               Tex  
     0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // top right
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,  0.0f, 1.0f // top left 
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

    // // Buffer Setup
    VAO VAO;
    VBO VBO(vertices, sizeof(vertices));
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
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Wrapping/filtering options   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load("resource/wall.jpg", &width, &height, &nrChannels, 0);
    if (data){
        GLenum imageType = nrChannels == 3 ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);


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
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        VAO.Bind();
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
