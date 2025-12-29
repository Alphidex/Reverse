#include "Light.h"

DirectionalLight::DirectionalLight(const glm::vec3& direction, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular) {
    dir = direction;
    Light::LightProperties(ambient, diffuse, specular);
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

void Light::LightProperties(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular) 
{ 
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}

void DirectionalLight::ShaderData(Shader& shader) {
    shader.Enable();
        
    glUniform3fv(glGetUniformLocation(shader.getID(), "dirLight.direction"), 1,  glm::value_ptr(dir));
    glUniform3fv(glGetUniformLocation(shader.getID(), "dirLight.ambient"), 1, glm::value_ptr(ambient));
    glUniform3fv(glGetUniformLocation(shader.getID(), "dirLight.diffuse"), 1,  glm::value_ptr(diffuse));
    glUniform3fv(glGetUniformLocation(shader.getID(), "dirLight.specular"), 1,  glm::value_ptr(specular));
}

void PointLight::ShaderData(Shader& shader) {
    shader.Enable();
    glUniform3fv(glGetUniformLocation(shader.getID(), "pointLight.position"), 1,  glm::value_ptr(pos));
    glUniform1fv(glGetUniformLocation(shader.getID(), "pointLight.constant"), 1,  &attConstant);
    glUniform1fv(glGetUniformLocation(shader.getID(), "pointLight.linear"), 1,  &attLinear);
    glUniform1fv(glGetUniformLocation(shader.getID(), "pointLight.quadratic"), 1, &attQuadratic);
    glUniform3fv(glGetUniformLocation(shader.getID(), "pointLight.ambient"), 1, glm::value_ptr(ambient));
    glUniform3fv(glGetUniformLocation(shader.getID(), "pointLight.diffuse"), 1,  glm::value_ptr(diffuse));
    glUniform3fv(glGetUniformLocation(shader.getID(), "pointLight.specular"), 1,  glm::value_ptr(specular));    
}

void SpotLight::ShaderData(Shader& shader) {
    shader.Enable();
    glUniform3fv(glGetUniformLocation(shader.getID(), "spotLight.direction"), 1,  glm::value_ptr(dir));
    glUniform3fv(glGetUniformLocation(shader.getID(), "spotLight.position"), 1,  glm::value_ptr(pos));
    glUniform3fv(glGetUniformLocation(shader.getID(), "spotLight.ambient"), 1, glm::value_ptr(ambient));
    glUniform3fv(glGetUniformLocation(shader.getID(), "spotLight.diffuse"), 1,  glm::value_ptr(diffuse));
    glUniform3fv(glGetUniformLocation(shader.getID(), "spotLight.specular"), 1,  glm::value_ptr(specular));
    glUniform1fv(glGetUniformLocation(shader.getID(), "spotLight.innerCutOff"), 1, &innerCutOff);
    glUniform1fv(glGetUniformLocation(shader.getID(), "spotLight.outerCutOff"), 1, &outerCutOff);
    
}