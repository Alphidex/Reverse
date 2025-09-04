#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightColor; 
uniform vec3 lightPos;
uniform vec3 cameraPos;

// Natural reflected color
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

uniform Material material;

// Light color * strength of components
struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;  

float distanceShading(float distance)
{
    return exp(-distance * 0.01);
}

void main()
{   
    // Constructor
    float distanceFromLight = length(lightPos - FragPos);
    float distanceDrawStrength = distanceShading(distanceFromLight);

    // Ambient
    vec3 ambient = vec3(texture(material.diffuse, texCoord)) * light.ambient;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = vec3(texture(material.diffuse, texCoord)) * light.diffuse * diff;

    // Specular
    vec3 reflLightDir = reflect(-lightDir, norm);
    vec3 cameraDir = normalize(cameraPos - FragPos);
    float spec = pow(max(dot(reflLightDir, cameraDir), 0.0), material.shininess);
    vec3 specular = vec3(texture(material.specular, texCoord)) * light.specular * spec;

    FragColor = vec4(ambient + diffuse + specular, 1.0);
} 