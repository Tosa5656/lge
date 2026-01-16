#include "../../include/Mesh/Mesh.h"

Mesh::Mesh()
{

}

Mesh::Mesh(std::vector<GLfloat>& vertices, std::vector<GLfloat>& colors, std::vector<GLuint>& indices, std::vector<GLfloat>& texpos)
{
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
    
    glVertexAttribPointer(2, 2, GL_FLOAT,GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glGenTextures(1, &mesh_texture);
    glBindTexture(GL_TEXTURE_2D, mesh_texture);

    int width, height;
    unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB); 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::Draw()
{
    glBindTexture(GL_TEXTURE_2D, mesh_texture);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawElements(GL_TRIANGLES, mesh_indices.size(), GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}