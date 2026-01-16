#include <iostream>
#include <vector>
#include <cstddef>

#include "../../../libs/glad/include/glad/gl.h"
#include "../../../libs/glfw/include/GLFW/glfw3.h"
class Mesh
{
public:
    Mesh();
    Mesh(std::vector<GLfloat>& vertices, std::vector<GLuint>& indices);
    ~Mesh();

    void Init();

    void Draw();
private:
    GLuint VAO, VBO, IBO;
    std::vector<GLfloat> mesh_vertices;
    std::vector<GLuint> mesh_indices;
    size_t mesh_vertexCount = 0;
};