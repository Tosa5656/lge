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


    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f  
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void RenderManager::Cleanup()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void RenderManager::RenderFrame()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}