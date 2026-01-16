#include "../../include/Render/RenderManager.h"

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
         0.0f,  0.5f, 0.0f  
    };
    
    test_mesh = Mesh(vertices);
    test_mesh.Init();
}

void RenderManager::Cleanup()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void RenderManager::RenderFrame()
{
    glUseProgram(shaderProgram);
    test_mesh.Draw();
}