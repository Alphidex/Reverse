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
    // Positions            // Texture Coords

    // Front face
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}}, // bottom-left
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}}, // bottom-right
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}}, // top-right
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f}}, // top-left

    // Back face
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}}, // bottom-right
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}}, // bottom-left
    {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}}, // top-left
    {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}}, // top-right

    // Left face
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}},
    {{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}},
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}},

    // Right face
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},

    // Top face
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}},
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},

    // Bottom face
    {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}},
    {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}}
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


    gladLoadGL();
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);
    
    // Callbacks
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 
    
    // Shader Setup
    Shader shaderProgram("shader/default.vert", "shader/default.frag");

    // Texture
    Texture texture("resource/wall.jpg", 0);

    // Mesh Setup
    Mesh mesh(vertices, indices, texture);

    // Camera
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    glfwSetScrollCallback(window, Scroll_Callback);

    // Curious what happens if I keep it out of while loop
    shaderProgram.Enable();
    glUniform1i(glGetUniformLocation(shaderProgram.ID, "sampledTexture"), 0);

    while(!glfwWindowShouldClose(window))
    {   
        auto startTime = glfwGetTime();

        glfwPollEvents();
        processInput(window);

        // Clears the back-buffer with said color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Drawing
        glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f), 
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

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));

        glm::mat4 cameraView;
        cameraView = camera.Inputs(window, deltaTime);

        glm::mat4 trans = glm::mat4(1.0f);

        for (int i = 0; i < 10; i++){
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, (float)glfwGetTime() + i * 15, glm::vec3(0.5f, 1.0f, 0.0f));
            trans = cameraView * model;
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
            mesh.Draw();
        }

        
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

        glfwSwapBuffers(window);

        auto endTime = glfwGetTime();
        deltaTime = endTime - startTime;
    }

    mesh.Delete();
    shaderProgram.Delete();

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
