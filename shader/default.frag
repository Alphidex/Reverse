#version 330 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D sampledTexture; 

void main()
{
    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    // texture(sampledTexture, texCoord)
} 