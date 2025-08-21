// System Packages
#include<iostream>
#include<stdexcept>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include <filesystem>
#include <thread>
#include <chrono>

// External Packages
#include<glad/glad.h> // Assigns function pointers since OpenGL is a specification
#include<GLFW/glfw3.h> // Create windows, assign context, poll events


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
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
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
    unsigned int vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertexCode   = getFileContents("shader/default.vert");
    std::string fragmentCode = getFileContents("shader/default.frag");

    const char* vertexShaderSource   = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();
    
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);
    shaderErrors(vertexShader, "SHADER");
    shaderErrors(fragmentShader,"SHADER");

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    shaderErrors(shaderProgram,"PROGRAM");

    // Save memory
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Buffer Setup
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Run this before VBO/EBO so VAO knows the configuration
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Curious what happens if I keep it out of while loop
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);

    while(!glfwWindowShouldClose(window))
    {   
        processInput(window);

        // Clears the back-buffer with said color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Drawing
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();    
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    
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

// Reads a text file and outputs a string with everything in the text file
std::string getFileContents(const char* filename)
{
	std::ifstream in(filename, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw std::runtime_error(std::string("Failed to open file: ") + filename);
}

void shaderErrors(unsigned int& shader, std::string type){
    int  success;
    char infoLog[512];
    if (type == "SHADER") glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    else if (type == "PROGRAM") glGetProgramiv(shader, GL_LINK_STATUS, &success);
    else return;

    if(!success) {
        glGetProgramInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR:: " << type << " ::FAILED! " << infoLog << std::endl;
    }
}