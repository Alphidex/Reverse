#include"project/Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath){
    // Shader Setup
    unsigned int vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertexCode   = readFile(vertexPath);
    std::string fragmentCode = readFile(fragmentPath);

    const char* vertexShaderSource   = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();
    
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);
    compileErrors(vertexShader, "SHADER");
    compileErrors(fragmentShader,"SHADER");

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);
    compileErrors(ID,"PROGRAM");

    // Save memory
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Enable(){
    glUseProgram(ID);
}

void Shader::Delete(){
    glDeleteShader(ID);
}

void Shader::compileErrors(unsigned int& shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if (type == "SHADER"){
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
                    << infoLog << "\n -- --------------------------------------------------- -- " 
                    << std::endl;
        }
    }
    else if (type == "PROGRAM"){
        GLint success;
        GLchar infoLog[1024];
        glGetProgramiv(shader, GL_LINK_STATUS, &success);

        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR\n"
                    << infoLog << "\n -- --------------------------------------------------- -- " 
                    << std::endl;
        }
    }
    else return;
}