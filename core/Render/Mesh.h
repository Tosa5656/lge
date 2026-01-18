#include <iostream>
#include <vector>
#include <cstddef>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <Render/Texture.h>

class Mesh
{
public:
    Mesh();
    Mesh(GLuint shaderProgram, std::vector<GLfloat>& vertices, std::vector<GLfloat>& colors, std::vector<GLuint>& indices, std::vector<GLfloat>& texpos);
    ~Mesh();

    void Init();

    void Draw();
private:
    GLuint VAO = 0;
    GLuint VBO_positions = 0;
    GLuint VBO_colors = 0;
    GLuint VBO_texpos = 0;
    GLuint IBO = 0;

    std::vector<GLfloat> mesh_vertices;
    std::vector<GLfloat> mesh_colors;
    std::vector<GLuint> mesh_indices;
    std::vector<GLfloat> mesh_texpos;
    size_t mesh_vertexCount = 0;

    GLuint mesh_shaderProgram;
    Texture mesh_texture;
};