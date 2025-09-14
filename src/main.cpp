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
#include <filesystem>

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
#include<project/Light.h>
#include<project/Model.h>


// Parameters
int width = 800;
int height = 800;

const int FPS = 60; 
const std::chrono::microseconds frameDuration(1'000'000 / FPS);
double deltaTime = 0;


// Callback Functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


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
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    // Shader Setup
    Shader shaderProgram("shader/default.vert", "shader/default.frag");
    Shader lightShader("shader/light.vert", "shader/light.frag");
    std::vector<Shader> shaderList = {shaderProgram, lightShader};

    // Models
    Model model("resource/backpack/backpack.obj");

    // Camera
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    glfwSetScrollCallback(window, Scroll_Callback);


    // Light
    glm::vec3 materialAmbient = glm::vec3(1.0f, 0.5f, 0.31f);
    glm::vec3 materialSpecular = glm::vec3(0.5, 0.5, 0.5);
    const float materialShininess = 32.0f;

    glm::vec3 lightColor =  glm::vec3(1.0, 1.0, 1.0);
    glm::vec3 lightPos = glm::vec3(5, 4, 1);
    glm::vec3 lightDirection = glm::vec3(0.2, -1, -0.3);

    glm::vec3 lightAmbient = glm::vec3(0.2, 0.2, 0.2);
    glm::vec3 lightDiffuse = glm::vec3(0.5, 0.5, 0.5);
    glm::vec3 lightSpecular = glm::vec3(1, 1, 1);

    float attenuationConstant = 1.0f;
    float attenuationLinear = 0.01f;
    float attenuationQuadratic = 0.001f;

    Light dirLight = Light::Directional(lightDirection);
    Light pointLight = Light::Point(lightPos, attenuationConstant, attenuationLinear, attenuationQuadratic);
    Light spotLight = Light::Spotlight(camera.Position, camera.Front, 2, 4);
    dirLight.LightProperties(lightAmbient, lightDiffuse, lightSpecular);
    pointLight.LightProperties(lightAmbient, lightDiffuse, lightSpecular);
    spotLight.LightProperties(lightAmbient, lightDiffuse, lightSpecular);

    // Sending Uniform Data
    lightShader.Enable();
    glUniform3fv(glGetUniformLocation(lightShader.ID, "lightColor"), 1, glm::value_ptr(lightColor));

    shaderProgram.Enable();

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
        model.Draw(shaderProgram);


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

    // Clean-up
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
