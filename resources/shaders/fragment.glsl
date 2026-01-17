#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture;

void main()
{
    vec4 textureColor = texture(ourTexture, TexCoord);
    color = textureColor * vec4(ourColor, 1.0f);
}