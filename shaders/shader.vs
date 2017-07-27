#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCord;

out vec3 vertexColor;
out vec2 texCord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    texCord = aTexCord;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}