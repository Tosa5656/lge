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
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    std::vector<GLfloat> colors = {
        1.0f,  1.0f, 1.0f,
        1.0f,  1.0f, 1.0f,
        1.0f,  1.0f, 1.0f,
        1.0f,  1.0f, 1.0f
    };
    
    std::vector<GLuint> indices = {
        0, 1, 2,
        0, 2, 3
    };

    std::vector<GLfloat> texpos = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
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