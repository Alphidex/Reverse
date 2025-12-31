// // ===== System =====
#include <iostream>
#include <vector>
#include <filesystem>
#include <glm/glm.hpp>

// // ===== Project =====
#include "Camera.h"
#include "Light.h"
#include "Model.h"
#include "Program.h"
#include "Interface.h"

using std::vector;


// Parameters
int width = 800;
int height = 800;

const float FPS = 60.0f; 
float deltaTime = 0.0f;
float lastFrame = 0.0f;



vector<Vertex> cube = {
    // Front face
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
    // Back face
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
};

vector<unsigned int> cubeIndices = {
    // Front face
    0, 1, 2,
    2, 3, 0,
    // Back face
    4, 5, 6,
    6, 7, 4,
    // Left face
    4, 0, 3,
    3, 7, 4,
    // Right face
    1, 5, 6,
    6, 2, 1,
    // Top face
    3, 2, 6,
    6, 7, 3,
    // Bottom face
    4, 5, 1,
    1, 0, 4
};

vector<Texture> cubeTextures = {};


int main(){
    std::cout << "Current Path: " << std::filesystem::current_path() << std::endl;
    /*
    {Program} contains all the GLFW/GLAD config settings.
    {Program} creates window, which must be passed to Interface class.
    */ 
    Program program(width, height);
    GLFWwindow* window = program.GetWindow();
    
    // Shader Setup
    Shader shaderProgram("shader/default.vert", "shader/default.frag");
    Shader interfaceProgram("shader/interface.vert", "shader/interface.frag");
    vector<Shader> shaderList = {shaderProgram};
    
    /* Interface Setup. Responsible for anythin UI related */
    Interface ui(window, interfaceProgram);
    // Container box(0.0, 0.0, 0.2, 0.7, window, interfaceProgram);
    // Container box2(0.0, 0.7, 1.0, 0.3, window, interfaceProgram); 
    Model model("resource/models/backpack/backpack.obj");
    Model sorceress("resource/models/sorceress/source/Sorcerrer_03.fbx");
    Model porshe("resource/models/porshe/source/PORSHE.blend");
    
    // Camera
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    glfwSetScrollCallback(window, Scroll_Callback);

    // Light
    glm::vec3 lightDir(0.0f, -1.0f, 0.0f);
    DirectionalLight dirLight(glm, 1.0f, 1.0f, 1.0f);

    while(program.Running())
    {   
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame; // Frame difference in seconds
        lastFrame = currentFrame;

        program.ProcessEvents();

        // Clears the back-buffer with said color
        ui.ClearBackgroundColor(0.2f, 0.3f, 0.3f, 1.0f);
        program.ClearBuffers();

        // Drawing
        // box.Draw();
        // box2.Draw();
        // model.Draw(shaderProgram);
        // sorceress.Draw(shaderProgram);
        // porshe.Draw(shaderProgram);
        camera.Update(window, deltaTime, shaderList, "cameraView");

        auto endTime = glfwGetTime();
        program.SwapBuffers();
    }

    // Cleaning Up
    program.Terminate();
    return 0;
}
