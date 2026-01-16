#include "../../include/Mesh/Mesh.h"

Mesh::Mesh()
{

}

Mesh::Mesh(std::vector<GLfloat>& vertices)
{
    mesh_vertices = vertices;
    mesh_vertexCount = vertices.size() / 3; 

    std::cout << "Calculated vertex count: " << mesh_vertexCount << std::endl;
}

Mesh::~Mesh()
{

}

void Mesh::Init()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh_vertices.size() * sizeof(GLfloat), mesh_vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Mesh::Draw()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, mesh_vertexCount);
    glBindVertexArray(0);
}