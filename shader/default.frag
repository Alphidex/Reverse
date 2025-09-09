#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 cameraPos;

// Natural reflected color
struct Material {
    sampler2D diffuse[3];
    sampler2D specular[3];
    float shininess;
}; 

uniform Material material;

// Light color * strength of components
// struct Light {
//     vec3 position;
  
//     vec3 ambient;
//     vec3 diffuse;
//     vec3 specular;
// };

// uniform Light light;  

struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  
uniform DirLight dirLight;

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform PointLight pointLight;

struct SpotLight {
    vec3 position;
    vec3 direction;
    float innerCutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform SpotLight spotLight;

vec3 CalcDirectionalLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir); 

void main()
{   
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(cameraPos - FragPos); 
    vec3 result = vec3(0.0);

    // result += CalcDirectionalLight(dirLight, normal, viewDir);
    // result += CalcPointLight(pointLight, normal, FragPos, viewDir);
    result += CalcSpotLight(spotLight, normal, FragPos, viewDir);

    FragColor = vec4(result, 1.0);
} 



// Funcion Definitions
vec3 CalcDirectionalLight(DirLight light, vec3 normal, vec3 viewDir)
{
    light.direction = normalize(-light.direction);

    // Ambient
    vec3 ambient = vec3(texture(material.diffuse, texCoord)) * light.ambient;

    // Diffuse
    float diff = max(dot(normal, light.direction), 0.0);
    vec3 diffuse = vec3(texture(material.diffuse, texCoord)) * light.diffuse * diff;

    // Specular
    vec3 lightRefl = reflect(-light.direction, normal);
    float spec = pow(max(dot(lightRefl, viewDir), 0.0), material.shininess);
    vec3 specular = vec3(texture(material.specular, texCoord)) * light.specular * spec;

    return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float dist = length(fragPos - light.position);
    float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

    // Ambient
    vec3 ambient = vec3(texture(material.diffuse, texCoord)) * light.ambient;

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = vec3(texture(material.diffuse, texCoord)) * light.diffuse * diff;

    // Specular
    vec3 lightRefl = reflect(-lightDir, normal);
    float spec = pow(max(dot(lightRefl, viewDir), 0.0), material.shininess);
    vec3 specular = vec3(texture(material.specular, texCoord)) * light.specular * spec;

    vec3 result = (ambient + diffuse + specular) * attenuation;
    return result;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) 
{
    vec3 lightDir = normalize(light.position - fragPos);

    float theta = max(dot(lightDir, normalize(-light.direction)), 0.0);
    float intensity = clamp((light.outerCutOff - theta) / (light.outerCutOff - light.innerCutOff), 0.0, 1.0);

    // Ambient
    vec3 ambient = vec3(texture(material.diffuse, texCoord)) * light.ambient;

    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = vec3(texture(material.diffuse, texCoord)) * light.diffuse * diff;

    // Specular
    vec3 lightRefl = reflect(-lightDir, normal);
    float spec = pow(max(dot(lightRefl, viewDir), 0.0), material.shininess);
    vec3 specular = vec3(texture(material.specular, texCoord)) * light.specular * spec;

    vec3 result = (ambient + diffuse + specular) * intensity;
    return result;
}