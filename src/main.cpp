#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include <iostream>
#include <fmt/core.h>

const int width = 800;
const int height = 800;

// Vertices coordinates
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Upper triangle
	5, 4, 1 // Lower right triangle
};


int main() {
    glfwInit();
    // Tell glfw3 contet info
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Reverse", NULL, NULL);
    if (window == NULL){
        fmt::print("Failed to create GLFW Window\n");
        glfwTerminate();
        return -1;
    }
    
    // Do this first otherwise window freezes
    glfwMakeContextCurrent(window);

    // Load GLAD to configure OpenGL
    gladLoadGL(); 

    // Tells OpenGL where to render
    glViewport(0, 0, width, height);
    Shader shaderProgram("src/default.vert", "src/default.frag");
	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkVBO(VBO1, 0);
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

    double time = 0;
    double flickerDuration = 0.1;
    double angle = 0; 

    while(!glfwWindowShouldClose(window))
    {   
        if (glfwGetTime() - time > flickerDuration){
            time = glfwGetTime();
            angle += 0.025;
        }

        // Tell OpenGL what background color to select
        glClearColor(sin(angle), cos(angle), tan(angle), 1.0f);

        // Tell OpenGL to replace the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
         
        glfwSwapBuffers(window);
        glfwPollEvents(); 
    }

	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
