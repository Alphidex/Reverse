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
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<imgui.h>
#include<imgui/backends/imgui_impl_glfw.h>
#include<imgui/backends/imgui_impl_opengl3.h>

// Project Packages
#include<project/Shader.h>
#include<project/VAO.h>
#include<project/VBO.h>
#include<project/EBO.h>
#include<project/Texture.h>
#include<project/Optional.h>
#include<project/Mesh.h>
#include<project/Camera.h>


// Parameters
int width = 800;
int height = 800;

const int FPS = 60; 
const std::chrono::microseconds frameDuration(1'000'000 / FPS);
double deltaTime = 0;


// Callback Functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
std::string getFileContents(const char* filename);
void shaderErrors(unsigned int& shader, std::string type);

// Data
std::vector<Vertex> vertices = {
    // Positions             // Color           // Texture Coords  // Normals
    // Front face (Z = 0.5)
    {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}, // bottom-left
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}, // bottom-right
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}, // top-right
    {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}, // top-left

    // Back face (Z = -0.5)
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 0.0f, -1.0f}}, // bottom-right
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}}, // bottom-left
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}}, // top-left
    {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 0.0f, -1.0f}}, // top-right

    // Left face (X = -0.5)
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}}, // bottom-right
    {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}}, // bottom-left
    {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}}, // top-left
    {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}}, // top-right

    // Right face (X = 0.5)
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}}, // bottom-right
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}}, // bottom-left
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}}, // top-left
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}}, // top-right

    // Top face (Y = 0.5)
    {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}, // bottom-left
    {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}}, // bottom-right
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}}, // top-right
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}, // top-left

    // Bottom face (Y = -0.5)
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}}, // top-right
    {{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}}, // bottom-right
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}}, // bottom-left
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}}  // top-left
};

std::vector<unsigned int> indices = {  
    // Front face
    0, 1, 2,  
    2, 3, 0,

    // Back face
    4, 5, 6,
    6, 7, 4,

    // Left face
    8, 9, 10,
    10, 11, 8,

    // Right face
    12, 13, 14,
    14, 15, 12,

    // Top face
    16, 17, 18,
    18, 19, 16,

    // Bottom face
    20, 21, 22,
    22, 23, 20
};




// TODO:
// Create a Light Class and make it Inherit from Mesh

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

    glEnable(GL_DEPTH_TEST);
    
    // Callback + Settings
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1); // use Vsync 

    // Debug window
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    // Shader Setup
    Shader shaderProgram("shader/default.vert", "shader/default.frag");
    Shader lightShader("shader/light.vert", "shader/light.frag");
    std::vector<Shader> shaderList = {shaderProgram, lightShader};


    // Texture
    Texture texture1("resource/container.png", 0);
    Texture texture2("resource/container_specular.png", 1);
    std::vector<Texture> textures = {texture1, texture2};
    std::vector<std::string> textureUniforms = {"material.diffuse", "material.specular"};

    // Mesh Setup
    Mesh regularCube(vertices, indices);
    regularCube.AddTextures(textures, textureUniforms);

    Mesh lightCube(vertices, indices);

    // Camera
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    glfwSetScrollCallback(window, Scroll_Callback);


    // Light Data - Easier for Debugging
    glm::vec3 lightColor =  glm::vec3(1.0, 1.0, 1.0);
    glm::vec3 lightPos = glm::vec3(5, 4, 1);

    // Sending Uniform Data
    for (Shader shader : shaderList)
    {
        shader.Enable();
        glUniform3fv(glGetUniformLocation(shader.ID, "lightColor"), 1, glm::value_ptr(lightColor));
    }

    glm::vec3 materialAmbient = glm::vec3(1.0f, 0.5f, 0.31f);
    glm::vec3 materialSpecular = glm::vec3(0.5, 0.5, 0.5);
    const float materialShininess = 32.0f;

    glm::vec3 lightAmbient = glm::vec3(0.2, 0.2, 0.2);
    glm::vec3 lightDiffuse = glm::vec3(0.5, 0.5, 0.5);
    glm::vec3 lightSpecular = glm::vec3(1, 1, 1);

    shaderProgram.Enable();
    glUniform3fv(glGetUniformLocation(shaderProgram.ID, "lightPos"), 1, glm::value_ptr(lightPos));
    glUniform3fv(glGetUniformLocation(shaderProgram.ID, "material.ambient"), 1, glm::value_ptr(materialAmbient));
    glUniform3fv(glGetUniformLocation(shaderProgram.ID, "material.diffuse"), 1,  glm::value_ptr(materialAmbient));
    glUniform3fv(glGetUniformLocation(shaderProgram.ID, "material.specular"), 1,  glm::value_ptr(materialSpecular));
    glUniform1fv(glGetUniformLocation(shaderProgram.ID, "material.shininess"), 1, &materialShininess);

    glUniform3fv(glGetUniformLocation(shaderProgram.ID, "light.ambient"), 1, glm::value_ptr(lightAmbient));
    glUniform3fv(glGetUniformLocation(shaderProgram.ID, "light.diffuse"), 1,  glm::value_ptr(lightDiffuse));
    glUniform3fv(glGetUniformLocation(shaderProgram.ID, "light.specular"), 1,  glm::value_ptr(lightSpecular));

    while(!glfwWindowShouldClose(window))
    {   
        auto startTime = glfwGetTime();

        glfwPollEvents();
        processInput(window);

        // Clears the back-buffer with said color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Drawing
        camera.Update(window, deltaTime, shaderList, "cameraView");

        std::vector<glm::vec3> cubePositions = {
            glm::vec3( 0.0f,  0.0f,  -2.0f), 
            glm::vec3( 2.0f,  5.0f, -15.0f), 
            glm::vec3(-1.5f, -2.2f, -2.5f),  
            glm::vec3(-3.8f, -2.0f, -12.3f),  
            glm::vec3( 2.4f, -0.4f, -3.5f),  
            glm::vec3(-1.7f,  3.0f, -7.5f),  
            glm::vec3( 1.3f, -2.0f, -2.5f),  
            glm::vec3( 1.5f,  2.0f, -2.5f), 
            glm::vec3( 1.5f,  0.2f, -1.5f), 
            glm::vec3(-1.3f,  1.0f, -1.5f)  
        };

        for (int i = 0; i < cubePositions.size(); i++){
            regularCube.ChangePosition(cubePositions[i]);
            regularCube.ChangeRotation((float)glfwGetTime() + i * 15, glm::vec3(0.5f, 1.0f, 0.0f));
            shaderProgram.Enable();
            glUniform3fv(glGetUniformLocation(shaderProgram.ID, "cameraPos"), 1, glm::value_ptr(camera.Position));
            regularCube.Draw(shaderProgram, "model");
        }
    
        lightCube.ChangePosition(lightPos);
        lightCube.Draw(lightShader, "model");


        // ------ Debugging ------
        // Start a new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Build your debug window
        ImGui::Begin("Debug Window");
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::Text("Position:  %.2f, %.2f, %.2f", 
            camera.Position.x, 
            camera.Position.y, 
            camera.Position.z);
        ImGui::Text("Front: %.2f, %.2f, %.2f", 
            camera.Front.x, 
            camera.Front.y, 
            camera.Front.z);

        ImGui::End();
        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // ------ End debugging ------

        glfwSwapBuffers(window);

        auto endTime = glfwGetTime();
        deltaTime = endTime - startTime;
    }

    for (Shader shader : shaderList){
        shader.Delete();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

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
