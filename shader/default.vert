#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 cameraView;

void main()
{
    gl_Position = cameraView * model * vec4(aPos, 1.0);
    texCoord = aTexCoord;
}