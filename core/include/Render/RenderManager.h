#include <iostream>

#include "../../../libs/glad/include/glad/gl.h"
#include "../../../libs/glfw/include/GLFW/glfw3.h"

class RenderManager
{
public:
    RenderManager();
    ~RenderManager();

    void Init();
    void Cleanup();

    void RenderFrame();
private:
    GLuint shaderProgram;
    GLuint VBO, VAO, IBO;
};