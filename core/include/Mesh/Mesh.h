#include <iostream>
#include <vector>
#include <cstddef>

#include "../../../libs/glad/include/glad/gl.h"
#include "../../../libs/glfw/include/GLFW/glfw3.h"
class Mesh
{
public:
    Mesh();
    Mesh(std::vector<GLfloat>& vertices);
    ~Mesh();

    void Init();

    void Draw();
private:
    GLuint VAO, VBO, EBO;
    std::vector<GLfloat> mesh_vertices;
    size_t mesh_vertexCount = 0;
};