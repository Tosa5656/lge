#include "Render/Mesh.h"

Mesh::Mesh()
{

}

Mesh::Mesh(GLuint shaderProgram, std::vector<GLfloat>& vertices, std::vector<GLfloat>& colors, std::vector<GLuint>& indices, std::vector<GLfloat>& texpos)
{
    mesh_shaderProgram = shaderProgram;

    mesh_vertices = vertices;
    mesh_vertexCount = vertices.size() / 3;

    mesh_colors = colors;

    mesh_indices = indices;

    mesh_texpos = texpos;
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO_positions);
    glDeleteBuffers(1, &IBO);
}

void Mesh::Init()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO_positions);
    glGenBuffers(1, &VBO_colors);
    glGenBuffers(1, &VBO_texpos);
    glGenBuffers(1, &IBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_positions);
    glBufferData(GL_ARRAY_BUFFER, mesh_vertices.size() * sizeof(GLfloat), mesh_vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh_indices.size() * sizeof(GLuint), mesh_indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_colors);
    glBufferData(GL_ARRAY_BUFFER, mesh_colors.size() * sizeof(GLfloat), mesh_colors.data(),  GL_STATIC_DRAW);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_texpos);
    glBufferData(GL_ARRAY_BUFFER, mesh_texpos.size() * sizeof(GLfloat), mesh_texpos.data(),  GL_STATIC_DRAW);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    //mesh_texture = Texture("container.jpg");
    //mesh_texture.Init();

    mesh_model = glm::mat4(1.0f);
    mesh_view = glm::mat4(1.0f);
    mesh_projection = glm::mat4(1.0f);

    mesh_model = glm::rotate(mesh_model, glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    mesh_model = glm::rotate(mesh_model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    mesh_view = glm::translate(mesh_view, glm::vec3(0.0f, 0.0f, -5.0f));

    mesh_projection = glm::perspective(glm::radians(45.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);
}

void Mesh::Draw()
{
    //glUniform1i(glGetUniformLocation(mesh_shaderProgram, "ourTexture"), 0);

    GLint modelLoc = glGetUniformLocation(mesh_shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(mesh_model));

    GLint viewLoc = glGetUniformLocation(mesh_shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(mesh_view));

    GLint projectionLoc = glGetUniformLocation(mesh_shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(mesh_projection));

    //mesh_texture.Enable();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawElements(GL_TRIANGLES, mesh_indices.size(), GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //mesh_texture.Disable();
}