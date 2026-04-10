/**
 * @file Light.cpp
 * @brief Implementation of the lighting system
 */

#include "header/Light.h"

DirectionalLight::DirectionalLight(const glm::vec3 direction, const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular) {
    dir = direction;
    Light::lightProperties(ambient, diffuse, specular);
}

PointLight::PointLight(const glm::vec3& direction, const glm::vec3& position, float constant, float linear, float quadratic) {
    dir = direction;
    pos = position;
    attConstant = constant;
    attLinear = linear;
    attQuadratic = quadratic;
}

SpotLight::SpotLight(const glm::vec3& direction, const glm::vec3& position, float cutOffInner, float cutOffOuter) {
    dir = direction;
    pos = position;
    innerCutOff = cutOffInner;
    outerCutOff = cutOffOuter;
}

void Light::lightProperties(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular) 
{ 
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}

void DirectionalLight::shaderData(Shader& shader) {
    shader.enable();
    
    shader.setVec3("dirLight.direction", dir);
    shader.setVec3("dirLight.ambient", ambient);
    shader.setVec3("dirLight.diffuse", diffuse);
    shader.setVec3("dirLight.specular", specular);
}

void PointLight::shaderData(Shader& shader) {
    shader.enable();
    
    shader.setVec3("pointLight.position", pos);
    shader.setFloat("pointLight.constant", attConstant);
    shader.setFloat("pointLight.linear", attLinear);
    shader.setFloat("pointLight.quadratic", attQuadratic);
    shader.setVec3("pointLight.ambient", ambient);
    shader.setVec3("pointLight.diffuse", diffuse);
    shader.setVec3("pointLight.specular", specular);
}

void SpotLight::shaderData(Shader& shader) {
    shader.enable();
    
    shader.setVec3("spotLight.direction", dir);
    shader.setVec3("spotLight.position", pos);
    shader.setVec3("spotLight.ambient", ambient);
    shader.setVec3("spotLight.diffuse", diffuse);
    shader.setVec3("spotLight.specular", specular);
    shader.setFloat("spotLight.innerCutOff", innerCutOff);
    shader.setFloat("spotLight.outerCutOff", outerCutOff);
}