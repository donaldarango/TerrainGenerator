#version 330 core
out vec4 FragColor;
  
in vec4 Color;
in vec2 TexCoord;   

uniform sampler2D terrainTexture;

void main()
{
    vec4 TexColor = texture(terrainTexture, TexCoord);
    FragColor = Color * TexColor;
}