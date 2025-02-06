#version 330 core
out vec4 FragColor;
  
in vec4 Color;
in vec2 TexCoord;  
in vec3 WorldPos;

uniform sampler2D Tex0;
uniform sampler2D Tex1;
uniform sampler2D Tex2;
uniform sampler2D Tex3;
uniform float maxHeight;
uniform float minHeight;

void main()
{
    float height = WorldPos.y;
    vec4 TexColor;

    float range1 = minHeight + 0.1 * (maxHeight - minHeight);
    float range2 = minHeight + 0.5 * (maxHeight - minHeight); // 0.1 + 0.4
    float range3 = minHeight + 0.7 * (maxHeight - minHeight); // 0.1 + 0.4 + 0.2

    vec4 tex1 = texture(Tex0, TexCoord);
    vec4 tex2 = texture(Tex1, TexCoord);
    vec4 tex3 = texture(Tex2, TexCoord);
    vec4 tex4 = texture(Tex3, TexCoord);

    if (height < range1) {
        TexColor = tex1;
    } else if (height < range2) {
        float factor = (height - range1) / (range2 - range1);
        TexColor = mix(tex1, tex2, factor);
    } else if (height < range3) {
        float factor = (height - range2) / (range3 - range2);
        TexColor = mix(tex2, tex3, factor);
    } else {
        float factor = (height - range3) / (maxHeight - range3);
        TexColor = mix(tex3, tex4, factor);
    }

    FragColor = Color * TexColor;
}