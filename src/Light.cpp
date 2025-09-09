#include<project/Light.h>

Light Light::Directional(const glm::vec3& direction) {
    Light l;
    l.Type = LightType::DIRECTIONAL;
    l.Direction = direction;
    return l;
}

Light Light::Point(const glm::vec3& position, float constant, float linear, float quadratic) {
    Light l;
    l.Type = LightType::POINTLIGHT;
    l.Position = position;
    l.attConstant = constant;
    l.attLinear = linear;
    l.attQuadratic = quadratic;
    return l;
}

Light Light::Spotlight(const glm::vec3& position, const glm::vec3& direction, float cutoffInner, float cutoffOuter) {
    Light l;
    l.Type = LightType::SPOTLIGHT;
    l.Position = position;
    l.Direction = direction;
    l.InnerCutOff = glm::cos(glm::radians(cutoffInner));
    l.OuterCutOff = glm::cos(glm::radians(cutoffOuter));

    return l;
}

void Light::LightProperties(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular) 
{ 
    Ambient = ambient;
    Diffuse = diffuse;
    Specular = specular;
};

void Light::ShaderData(Shader& shader)
{
    shader.Enable();
    
    if (Type == DIRECTIONAL)
    {
        glUniform3fv(glGetUniformLocation(shader.ID, "dirLight.direction"), 1,  glm::value_ptr(Direction));
        glUniform3fv(glGetUniformLocation(shader.ID, "dirLight.ambient"), 1, glm::value_ptr(Ambient));
        glUniform3fv(glGetUniformLocation(shader.ID, "dirLight.diffuse"), 1,  glm::value_ptr(Diffuse));
        glUniform3fv(glGetUniformLocation(shader.ID, "dirLight.specular"), 1,  glm::value_ptr(Specular));
    }
    if (Type == POINTLIGHT)
    {
        glUniform3fv(glGetUniformLocation(shader.ID, "pointLight.position"), 1,  glm::value_ptr(Position));
        glUniform1fv(glGetUniformLocation(shader.ID, "pointLight.constant"), 1,  &attConstant);
        glUniform1fv(glGetUniformLocation(shader.ID, "pointLight.linear"), 1,  &attLinear);
        glUniform1fv(glGetUniformLocation(shader.ID, "pointLight.quadratic"), 1, &attQuadratic);
        glUniform3fv(glGetUniformLocation(shader.ID, "pointLight.ambient"), 1, glm::value_ptr(Ambient));
        glUniform3fv(glGetUniformLocation(shader.ID, "pointLight.diffuse"), 1,  glm::value_ptr(Diffuse));
        glUniform3fv(glGetUniformLocation(shader.ID, "pointLight.specular"), 1,  glm::value_ptr(Specular));
    }

    if (Type == SPOTLIGHT)
    {
        glUniform3fv(glGetUniformLocation(shader.ID, "spotLight.direction"), 1,  glm::value_ptr(Direction));
        glUniform3fv(glGetUniformLocation(shader.ID, "spotLight.position"), 1,  glm::value_ptr(Position));
        glUniform3fv(glGetUniformLocation(shader.ID, "spotLight.ambient"), 1, glm::value_ptr(Ambient));
        glUniform3fv(glGetUniformLocation(shader.ID, "spotLight.diffuse"), 1,  glm::value_ptr(Diffuse));
        glUniform3fv(glGetUniformLocation(shader.ID, "spotLight.specular"), 1,  glm::value_ptr(Specular));
        glUniform1fv(glGetUniformLocation(shader.ID, "spotLight.innerCutOff"), 1, &InnerCutOff);
        glUniform1fv(glGetUniformLocation(shader.ID, "spotLight.outerCutOff"), 1, &OuterCutOff);
    }
}