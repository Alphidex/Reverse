#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture0;
uniform vec3 lightColor; 
uniform vec3 lightPos;
uniform vec3 cameraPos;

void main()
{   
    vec3 objectColor = vec3(0.3, 0.5, 0.31);

    // Ambient
    float ambientStrength = 0.3;
    vec3 ambient = lightColor * ambientStrength;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 diffuse = max(dot(norm, lightDir), 0.0) * lightColor;

    // Specular
    float specularStrength = 0.5;
    vec3 reflLightDir = reflect(-lightDir, norm);
    vec3 cameraDir = normalize(cameraPos, FragPos);
    vec3 specular = pow(max(dot(reflLightDir, cameraDir), 0.0), 32) * specularStrength * lightColor;


    FragColor = vec4(objectColor * (ambient + diffuse + specular), 1.0);
} 