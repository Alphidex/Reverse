#ifndef LIGHT_H
#define LIGHT_H
#include<glad/glad.h>
#include<glfw/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<project/Shader.h>

enum LightType 
{ 
    DIRECTIONAL, 
    POINTLIGHT, 
    SPOTLIGHT
};

class Light {
public:
    static Light Directional(const glm::vec3& direction);
    static Light Point(const glm::vec3& position, float constant, float linear, float quadratic);
    static Light Spotlight(const glm::vec3& position, const glm::vec3& direction, float cutoffInner, float cutoffOuter);
    void LightProperties(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);

    void ShaderData(Shader& shader);

    glm::vec3 Position{};
    glm::vec3 Direction{};

private:
    LightType Type;
    glm::vec3 Ambient{};
    glm::vec3 Diffuse{};
    glm::vec3 Specular{};

    float attConstant;
    float attLinear{};
    float attQuadratic;
    float InnerCutOff{};
    float OuterCutOff{};
};


#endif