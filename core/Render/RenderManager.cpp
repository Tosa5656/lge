#include "Render/RenderManager.h"

RenderManager::RenderManager()
{

}

RenderManager::~RenderManager()
{

}

void RenderManager::Init()
{
    GLuint vertexShader = ShaderManager::CreateShader("shaders/vertex.glsl", GL_VERTEX_SHADER);
    GLuint fragmentShader = ShaderManager::CreateShader("shaders/fragment.glsl", GL_FRAGMENT_SHADER);

    shaderProgram = ShaderManager::CreateShaderProgram(vertexShader, fragmentShader);


    std::vector<GLfloat> vertices = {
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
    };

    std::vector<GLfloat> colors = {
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
        0.5f,  0.3f,  0.8f,
    };
    
    std::vector<GLuint> indices = {
        0,  1,  2,
        0,  2,  3,
        4,  5,  6,
        4,  6,  7,
        8,  9,  10,
        8,  10, 11,
        12, 13, 14,
        12, 14, 15,
        16, 17, 18,
        16, 18, 19,
        20, 21, 22,
        20, 22, 23
    };

    std::vector<GLfloat> texpos = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
    };
    
    test_mesh = Mesh(shaderProgram, vertices, colors, indices, texpos);
    test_mesh.Init();
}

void RenderManager::Cleanup()
{
    
}

void RenderManager::RenderFrame()
{
    glUseProgram(shaderProgram);

    test_mesh.Draw();
}