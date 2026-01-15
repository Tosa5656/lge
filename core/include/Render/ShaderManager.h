#include <iostream>
#include <fstream>
#include <sstream>

#include "../../../libs/glad/include/glad/gl.h"

class ShaderManager
{
public:
    ShaderManager();
    ~ShaderManager();

    static GLuint CreateShader(std::string shaderPath, GLenum shaderType);
    static GLuint CreateShaderProgram(GLuint vertexShader, GLuint fragmentShader);
private:
    static std::string ReadShaderFile(std::string shaderPath);
};