#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Shader.h"

enum LightType 
{ 
    DIRECTIONAL, 
    POINTLIGHT, 
    SPOTLIGHT
};

class Light {
public:
    void LightProperties(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);
    void ShaderData(Shader& shader);
    
protected:
    glm::vec3 dir;
    glm::vec3 pos;
    LightType Type;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float attConstant;
    float attLinear;
    float attQuadratic;
};

class DirectionalLight : public Light {
public:
    DirectionalLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);
    void ShaderData(Shader& shader);
};

class PointLight : public Light {
public: 
    PointLight(const glm::vec3& direction, const glm::vec3& position, float constant, float linear, float quadratic);
    void ShaderData(Shader& shader);
};

class SpotLight : public Light {
public:
    SpotLight(const glm::vec3& direction, const glm::vec3& position, float cutOffInner, float cutOffOuter);
    void ShaderData(Shader& shader);

private:
    float innerCutOff;
    float outerCutOff;
};
