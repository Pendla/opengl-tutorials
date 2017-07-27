#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCord;

out vec3 vertexColor;
out vec2 texCord;

uniform mat4 trans;

void main()
{
    texCord = aTexCord;
    vertexColor = aColor;
    gl_Position = trans * vec4(aPos, 1.0);
}