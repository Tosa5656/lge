#version 330 core

in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture;

void main()
{
    float edgeThreshold = 0.005;

    bool isNearEdge = (TexCoord.x < edgeThreshold || TexCoord.x > (1.0 - edgeThreshold) || TexCoord.y < edgeThreshold || TexCoord.y > (1.0 - edgeThreshold));

    if (isNearEdge)
        color = vec4(0.0, 0.0, 0.0, 1.0);
    else
        color = vec4(ourColor, 1.0f);
}