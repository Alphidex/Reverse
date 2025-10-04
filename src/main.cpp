#include<SystemIncludes.h>
#include<ExternalIncludes.h>
#include<ProjectIncludes.h>


// Parameters
int width = 800;
int height = 800;

const int FPS = 60; 
double deltaTime = 0;

int main(){
    // As it starts out in: "C:\\Users\\.User\\Desktop\\Reverse\\out\\build\\default"
    std::filesystem::current_path(std::filesystem::path(__FILE__).parent_path().parent_path());
    std::cout << "Working directory: " << std::filesystem::current_path() << std::endl;

    /*
    {Program} contains all the GLFW/GLAD config settings.
    {Program} creates window, which must be passed to Interface class.
    */ 
    Program program(width, height);

    /* Interface Setup. Responsible for anythin UI related */
    GLFWwindow* window = program.GetWindow();
    Interface interface(width, height, window);

    // Shader Setup
    // Shader shaderProgram("shader/default.vert", "shader/default.frag");
    // shaderProgram.Enable();

    // Camera
    // Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    // glfwSetScrollCallback(window, Scroll_Callback);

    while(interface.IsOpen())
    {   
        auto startTime = glfwGetTime();

        program.ProcessEvents();

        // Clears the back-buffer with said color
        interface.ClearBackgroundColor(0.2f, 0.3f, 0.3f, 1.0f);
        program.ClearBuffers();

        // // Drawing
        // camera.Update(window, deltaTime, shaderList, "cameraView");
        // model.Draw(shaderProgram);

        auto endTime = glfwGetTime();
        deltaTime = endTime - startTime;

        program.SwapBuffers();
    }

    // Cleaning Up
    program.Terminate();
    return 0;
}
