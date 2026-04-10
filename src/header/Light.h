/**
 * @file Light.h
 * @brief Lighting system for scene illumination
 * @details Provides directional, point, and spotlight implementations
 */

#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Shader.h"

/// @brief Types of light sources
enum LightType 
{ 
    DIRECTIONAL,  ///< Directional light (like sun)
    POINTLIGHT,   ///< Point light (like bulb)
    SPOTLIGHT     ///< Spotlight (like flashlight)
};

/**
 * @brief Base class for light sources
 * @details Contains common properties shared by all light types
 */
class Light {
public:
    /**
     * @brief Sets the light's color properties
     * @param ambient Ambient light contribution
     * @param diffuse Diffuse light contribution
     * @param specular Specular highlight contribution
     */
    void lightProperties(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);
    
    /**
     * @brief Uploads light data to shader uniforms
     * @param shader Shader to update
     */
    void shaderData(Shader& shader);
    
protected:
    glm::vec3 dir;      ///< Light direction
    glm::vec3 pos;      ///< Light position
    LightType Type;     ///< Light type identifier
    glm::vec3 ambient;  ///< Ambient color
    glm::vec3 diffuse;  ///< Diffuse color
    glm::vec3 specular; ///< Specular color

    float attConstant;  ///< Constant attenuation factor
    float attLinear;    ///< Linear attenuation factor
    float attQuadratic; ///< Quadratic attenuation factor
};

/**
 * @brief Directional light (e.g., sun)
 * @details Provides parallel light rays from a specific direction
 */
class DirectionalLight : public Light {
public:
    /**
     * @brief Creates a directional light
     * @param direction Light direction vector
     * @param ambient Ambient light intensity
     * @param diffuse Diffuse light intensity
     * @param specular Specular light intensity
     */
    DirectionalLight(const glm::vec3 direction, const glm::vec3 ambient, const glm::vec3 diffuse, const glm::vec3 specular);
    
    /**
     * @brief Uploads directional light data to shader
     * @param shader Shader to update
     */
    void shaderData(Shader& shader);
};

/**
 * @brief Point light (e.g., light bulb)
 * @details Emits light in all directions from a point with distance attenuation
 */
class PointLight : public Light {
public:
    /**
     * @brief Creates a point light
     * @param direction Light direction (for reference)
     * @param position Light world position
     * @param constant Constant attenuation
     * @param linear Linear attenuation
     * @param quadratic Quadratic attenuation
     */
    PointLight(const glm::vec3& direction, const glm::vec3& position, float constant, float linear, float quadratic);
    
    /**
     * @brief Uploads point light data to shader
     * @param shader Shader to update
     */
    void shaderData(Shader& shader);
};

/**
 * @brief Spotlight (e.g., flashlight)
 * @details Conical light with inner and outer cutoff angles
 */
class SpotLight : public Light {
public:
    /**
     * @brief Creates a spotlight
     * @param direction Light direction
     * @param position Light world position
     * @param cutOffInner Inner cone angle (full intensity)
     * @param cutOffOuter Outer cone angle (fade to zero)
     */
    SpotLight(const glm::vec3& direction, const glm::vec3& position, float cutOffInner, float cutOffOuter);
    
    /**
     * @brief Uploads spotlight data to shader
     * @param shader Shader to update
     */
    void shaderData(Shader& shader);

private:
    float innerCutOff; ///< Inner cone angle
    float outerCutOff; ///< Outer cone angle
};
