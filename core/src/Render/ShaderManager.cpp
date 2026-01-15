#include "../../include/Render/ShaderManager.h"

ShaderManager::ShaderManager()
{

}

ShaderManager::~ShaderManager()
{

}

std::string ShaderManager::ReadShaderFile(std::string shaderPath)
{
    std::string shaderCode;
    std::ifstream shaderFile;
    
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    try
    {
        shaderFile.open(shaderPath);
        std::stringstream shaderStream;
        
        shaderStream << shaderFile.rdbuf();
        
        shaderFile.close();
        
        shaderCode = shaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " 
                  << shaderPath << std::endl;
        std::cout << "Exception: " << e.what() << std::endl;
        return "";
    }
    
    return shaderCode;
}

GLuint ShaderManager::CreateShader(std::string shaderPath, GLenum shaderType)
{
    std::string shaderCodeStr = ReadShaderFile(shaderPath);
    if (shaderCodeStr.empty())
        return 0;
    
    GLuint shader = glCreateShader(shaderType);
    
    // Конвертируем строку в C-style строку
    const char* shaderCode = shaderCodeStr.c_str();
    
    // Устанавливаем исходный код шейдера
    glShaderSource(shader, 1, &shaderCode, NULL);
    
    // Компилируем шейдер
    glCompileShader(shader);
    
    // Проверяем ошибки компиляции (сохраняя ваш стиль)
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" 
                  << "File: " << shaderPath << "\n" 
                  << infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }
    
    return shader;
}