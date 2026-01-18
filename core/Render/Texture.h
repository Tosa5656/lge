#include <iostream>

#include <glad/gl.h>
#include <SOIL/SOIL.h>

class Texture
{
public:
    Texture() {};
    Texture(std::string path);
    ~Texture();

    void Init();

    void Enable();
    void Disable();
private:
    std::string texturePath;
    GLuint texture;
};