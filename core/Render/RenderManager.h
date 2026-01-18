#pragma once

#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "ShaderManager.h"
#include "Mesh.h"

class RenderManager
{
public:
    RenderManager();
    ~RenderManager();

    void Init();
    void Cleanup();

    void RenderFrame();
private:
    GLuint shaderProgram;
    GLuint VBO, VAO, IBO;

    Mesh test_mesh = Mesh();
};