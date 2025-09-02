#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture0;
uniform vec3 lightColor; 
uniform vec3 lightPos;

void main()
{   
    vec3 objectColor = vec3(0.3, 0.5, 0.31);

    // Ambient
    float ambientStrength = 0.3;
    vec3 ambient = lightColor * ambientStrength;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diffStrength = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffStrength * lightColor;


    FragColor = vec4(objectColor * (ambient + diffuse), 1.0);
} 