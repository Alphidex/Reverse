// ===== System =====
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>
#include <filesystem>
#include <thread>
#include <chrono>
#include <vector>

// ===== External =====
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// ===== Project =====
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Optional.h"
#include "Mesh.h"
#include "Camera.h"
#include "Light.h"
#include "Model.h"`
#include "Program.h"
#include "Interface.h"


// Parameters
int width = 800;
int height = 800;

const int FPS = 60; 
double deltaTime = 0;

int main(){
    /*
    {Program} contains all the GLFW/GLAD config settings.
    {Program} creates window, which must be passed to Interface class.
    */ 
    Program program(width, height);
    GLFWwindow* window = program.GetWindow();
    
    // Shader Setup
    Shader shaderProgram("shader/default.vert", "shader/default.frag");
    Shader interfaceProgram("shader/interface.vert", "shader/interface.frag");
    
    /* Interface Setup. Responsible for anythin UI related */
    Interface ui(window, interfaceProgram);
    Container box(0.2, 0.2, 0.7, 0.4, window, interfaceProgram); 
    
    // Camera
    // Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    // glfwSetScrollCallback(window, Scroll_Callback);

    while(program.Running())
    {   
        auto startTime = glfwGetTime();

        program.ProcessEvents();

        // Clears the back-buffer with said color
        ui.ClearBackgroundColor(0.2f, 0.3f, 0.3f, 1.0f);
        program.ClearBuffers();

        // // Drawing
        // camera.Update(window, deltaTime, shaderList, "cameraView");
        // model.Draw(shaderProgram);
        box.Draw();

        auto endTime = glfwGetTime();
        deltaTime = endTime - startTime;

        program.SwapBuffers();
    }

    // Cleaning Up
    program.Terminate();
    return 0;
}
