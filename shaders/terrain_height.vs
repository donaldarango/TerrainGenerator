#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 Color;
out vec2 TexCoord;
out vec3 WorldPos;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    Color = vec4(1.0f);
    TexCoord = aTexCoord;
    WorldPos = aPos;
}